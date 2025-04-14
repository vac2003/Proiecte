main :-
    open("Program.cs", read, Fisier), % read este modul de deschidere a fisierulu (citire/scriere).
    preluare_lista_caractere_fisier(Fisier, ListaCaractere),
    close(Fisier),

    % Meniu cu optiunile disponibile.
    writeln("ATENTIE: Acest analizor functioneaza doar pentru linii de cod in limbajul de programare C#!"),
    writeln("DE FACUT: separat optiunea 6 in optiunile 6 (cuvinte contextuale) si 7 (nume de functii/metode si la 7 sa se scoata cuvintele cheie)"),
    writeln("Optiuni:"),
    writeln("1. CONSTANTE SIR DE CARACTERE"),
    writeln("2. CONSTANTE NUMERICE"),
    writeln("3. SEPARATORI"),
    writeln("4. OPERATORI"),
    writeln("5. CUVINTE CHEIE (SAU CUVINTE REZERVATE)"),
    writeln("6. CUVINTE CONTEXTUALE"),

    % Citeste optiunea utilizatorului.
    get_char(Opt),

    % Obtine lista cu constante string.
    preluare_lista_constante_sir_caractere(ListaCaractere, ListaPreSir),
    elimina_elemente_duplicate_lista_de_liste(ListaPreSir, ListaConstanteSir),

    % Obtine lista cu constante numerice.
    preluare_lista_constante_numerice(ListaCaractere, ListaPreNum),
    elimina_elemente_duplicate_lista_de_liste(ListaPreNum, ListaConstanteNumerice),

    % Obtine lista cu separatori.
    preluare_lista_separatori(ListaCaractere, ListaPreSep),
    elimina_elemente_duplicate_lista_de_liste(ListaPreSep, ListaSeparatori),

    % Obtine lista cu operatori.
    preluare_lista_operatori(ListaCaractere, ListaPreOp),
    elimina_elemente_duplicate_lista_de_liste(ListaPreOp, ListaOperatori),

    % Obtine lista cu cuvinte cheie (cuvinte CONTEXTUALE).
    preluare_lista_cuvinte_contextuale(ListaCaractere, ListaPreCuvCheie),
    elimina_elemente_duplicate_lista_de_liste(ListaPreCuvCheie, ListaCuvinteContextuale),

    % Obtine lista cu cuvinte cheie (cuvinte REZERVATE).
    preluare_lista_cuvinte_cheie(ListaCaractere, ListaPreCuvRezervate),
    elimina_elemente_duplicate_lista_de_liste(ListaPreCuvRezervate, ListaCuvinteCheie),

    % Obtine 3 liste (spatii de nume, clase si structuri)
    preluare_lista_identificatori_ns_cl_st(ListaCaractere, ListaPreNS, ListaPrePreCL, ListaPrePreST, 0),
    elimina_elemente_duplicate_lista_de_liste(ListaPreNS, ListaIdentificatoriNamespace),
    elimina_elemente_duplicate_lista_de_liste(ListaPrePreCL, ListaPreCL),
    elimina_elemente_duplicate_lista_de_liste(ListaPrePreST, ListaPreST),

    preluare_lista_identificatori_var(ListaCaractere, ListaPreVar),
    elimina_elemente_duplicate_lista_de_liste(ListaPreVar, ListaIdentificatoriVariabile),

    preluare_lista_identificatori_metode(ListaIdentificatoriVariabile, ListaPreMet),
    elimina_elemente_duplicate_lista_de_liste(ListaPreMet, ListaIdentificatoriMetode),

    (   Opt == '1'
    ->  writeln("CONSTANTELE SIR DE CARACTERE SUNT:"),
        afisare_lista_de_liste(ListaConstanteSir),
        writeln("CONSTANTELE NUMERICE SUNT:"),
        afisare_lista_de_liste(ListaConstanteNumerice)
    ;   Opt == '2'
    ->  writeln("SEPARATORII SUNT:"),
        afisare_lista_de_liste(ListaSeparatori)
    ;   Opt == '3'
    ->  writeln("OPERATORII SUNT:"),
        afisare_lista_de_liste(ListaOperatori)
    ;   Opt == '4'
    ->  writeln("CUVINTELE CHEIE (SAU CUVINTE REZERVATE) SUNT:"),
        afisare_lista_de_liste(ListaCuvinteCheie)
    
    ;   Opt == '5'
    ->  writeln("CUVINTELE CONTEXTUALE SUNT:"),
        afisare_lista_de_liste(ListaCuvinteContextuale)
    ; Opt == '6'
    ->  writeln("IDENTIFICATORII DE NAMESPACE SUNT: "),
        writeln(""),
        writeln("1. SPATII DE NUME"),
        afisare_lista_de_liste(ListaIdentificatoriNamespace),
        writeln(""),
        writeln("2. CLASE"),
        afisare_lista_de_liste(ListaIdentificatoriClase),
        writeln(""),
        writeln("3. STRUCTURI"),
        afisare_lista_de_liste(ListaIdentificatoriStructuri),
        get_char(T),    
        writeln(""),
        writeln("4. IDENTIFICATORI VARIABILE/CONSTANTE"),
        afisare_lista_de_liste(ListaIdentificatoriVariabile),
        get_char(TT),
        writeln(""),
        writeln("5. METODE"),
        afisare_lista_de_liste(ListaIdentificatoriMetode)

    ; Opt == 7
    -> writeln("NU EXISTA IDENTIFICATORI DE PREDICATE")

    ).

% Predicat pentru a obine o lista cu toate caracterele in fisierul
% sursa.
preluare_lista_caractere_fisier(Fisier, ListaCaractere) :-
    read_string(Fisier, _, CodText), % Al doilea parametru este lungimea textului asa ca ii punem _ deoarece nu ne intereseaza ce valoare are.
    string_chars(CodText, ListaTemp), % Lista
    elimina_comentarii(ListaTemp, ListaCaractere).

% Predicatul elimina comentariile din lista de caractere (// inceput de comentariu si \n sfarsit de comentariu).
elimina_comentarii([], []).

elimina_comentarii(['/', '*' | RL], LF) :-
    ignora_comentariul_multi(RL, ListaDupaIgnorare),
    elimina_comentarii(ListaDupaIgnorare, LF).

elimina_comentarii(['/','/' | RL], LF) :-
    ignora_comentariul_mono(RL, ListaDupaIgnorare),
    elimina_comentarii(ListaDupaIgnorare, LF).

elimina_comentarii([E | RL], [E | LF]) :-
    elimina_comentarii(RL, LF).

% Predicat ajutator, daca se gaseste un comentariu se trece peste caracterele aflate in comentariu incluzand // si \n.
ignora_comentariul_mono([], []).
ignora_comentariul_mono(['\n' | RL], ['\n' | RL]).
ignora_comentariul_mono([_ | RL], LF) :- ignora_comentariul_mono(RL, LF).

ignora_comentariul_multi([], []).
ignora_comentariul_multi(['*', '/' | RL], RL).
ignora_comentariul_multi([_ | RL], LF) :- ignora_comentariul_multi(RL, LF).

% Predicat pentru a extrage constantele de tip sir de caractere intr-o lista de liste.
preluare_lista_constante_sir_caractere([], []).
preluare_lista_constante_sir_caractere([E | RL], LCS) :-
    E \= '"',
    preluare_lista_constante_sir_caractere(RL, LCS).
preluare_lista_constante_sir_caractere(['"' | RL], [Constanta | RLCS]) :-
    extrage_constanta_sir_caractere(RL, Temp, ListaDupaExtragere),
    Constanta = ['"' | Temp],
    preluare_lista_constante_sir_caractere(ListaDupaExtragere, RLCS).

extrage_constanta_sir_caractere([], [], []).
extrage_constanta_sir_caractere(['"' | RL], ['"'], RL).
extrage_constanta_sir_caractere([E | RL], [E | RLCS], LDE) :-
    extrage_constanta_sir_caractere(RL, RLCS, LDE).

% Predicat pentru a gasi constantele numerice.
preluare_lista_constante_numerice([], []).
preluare_lista_constante_numerice(['"' | RL], LCN) :-
    ignora_constanta_sir_caractere(RL, ListaDupaIgnorare),
    preluare_lista_constante_numerice(ListaDupaIgnorare, LCN).
preluare_lista_constante_numerice([E1, E2 | RL], LCN) :-
    (este_litera_mica(E1) ; este_litera_mare(E1) ; este_underscore(E1)),
    este_numar(E2),
    ignora_cifre_identificator(RL, ListaDupaIgnorare),
    preluare_lista_constante_numerice(ListaDupaIgnorare, LCN).
preluare_lista_constante_numerice([E | RL], LCN) :-
    \+ este_numar(E),
    preluare_lista_constante_numerice(RL, LCN).
preluare_lista_constante_numerice([E | RL], [Constanta | RLCN]) :-
    extrage_constanta_numerica(RL, Temp, ListaDupaExtragere),
    Constanta = [E | Temp],
    preluare_lista_constante_numerice(ListaDupaExtragere, RLCN).

extrage_constanta_numerica([], [], []).

extrage_constanta_numerica([E | RL], [], [E | RL]) :- \+ este_numar(E).

extrage_constanta_numerica([E | RL], [E | RLCN], LDE) :- extrage_constanta_numerica(RL, RLCN, LDE).

% Predicat pentru a obtine o lista cu separatorii.
preluare_lista_separatori([], []).

preluare_lista_separatori(['"' | RL], LS) :-
    ignora_constanta_sir_caractere(RL, ListaDupaIgnorare),
    preluare_lista_separatori(ListaDupaIgnorare, LS).

preluare_lista_separatori([E1, E2 | RL], [[E1, E2] | LS]) :-
    este_separator2(E1, E2),
    preluare_lista_separatori(RL, LS).

preluare_lista_separatori([E | RL], LS) :-
    \+ este_separator(E),
    preluare_lista_separatori(RL, LS).

preluare_lista_separatori([E | RL], [[E] | RLS]) :-
    preluare_lista_separatori(RL, RLS).

% Predicat pentru a obtine o lista cu operatorii.
preluare_lista_operatori([], []).

preluare_lista_operatori(['"' | RL], LO) :-
    ignora_constanta_sir_caractere(RL, ListaDupaIgnorare),
    preluare_lista_operatori(ListaDupaIgnorare, LO).

preluare_lista_operatori([E1, E2, E3 | RL], [[E1, E2, E3] | LO]) :-
    este_operator3(E1, E2, E3),
    preluare_lista_operatori(RL, LO).

preluare_lista_operatori([E1, E2 | RL], [[E1, E2] | LO]) :-
    este_operator2(E1, E2),
    preluare_lista_operatori(RL, LO).

preluare_lista_operatori([E | RL], LO) :-
    \+ este_operator(E),
    preluare_lista_operatori(RL, LO).

preluare_lista_operatori([E | RL], [[E] | RLO]) :-
    preluare_lista_operatori(RL, RLO).

% Predicat pentru a obtine o lista cu cuvintele cheie.
preluare_lista_cuvinte_contextuale([], []).

preluare_lista_cuvinte_contextuale(['"' | RL], LCC) :-
    ignora_constanta_sir_caractere(RL, ListaDupaIgnorare),
    preluare_lista_cuvinte_contextuale(ListaDupaIgnorare, LCC).

preluare_lista_cuvinte_contextuale([S1, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, S2 | RL], [[E1, E2, E3, E4, E5, E6, E7, E8, E9, E10] | LCC]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_cheie10(E1, E2, E3, E4, E5, E6, E7, E8, E9, E10),
    preluare_lista_cuvinte_contextuale(RL, LCC).

preluare_lista_cuvinte_contextuale([S1, E1, E2, E3, E4, E5, E6, E7, E8, E9, S2 | RL], [[E1, E2, E3, E4, E5, E6, E7, E8, E9] | LCC]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_cheie9(E1, E2, E3, E4, E5, E6, E7, E8, E9),
    preluare_lista_cuvinte_contextuale(RL, LCC).

preluare_lista_cuvinte_contextuale([S1, E1, E2, E3, E4, E5, E6, E7, E8, S2 | RL], [[E1, E2, E3, E4, E5, E6, E7, E8] | LCC]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_cheie8(E1, E2, E3, E4, E5, E6, E7, E8),
    preluare_lista_cuvinte_contextuale(RL, LCC).

preluare_lista_cuvinte_contextuale([S1, E1, E2, E3, E4, E5, E6, E7, S2 | RL], [[E1, E2, E3, E4, E5, E6, E7] | LCC]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_cheie7(E1, E2, E3, E4, E5, E6, E7),
    preluare_lista_cuvinte_contextuale(RL, LCC).

preluare_lista_cuvinte_contextuale([S1, E1, E2, E3, E4, E5, E6, S2 | RL], [[E1, E2, E3, E4, E5, E6] | LCC]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_cheie6(E1, E2, E3, E4, E5, E6),
    preluare_lista_cuvinte_contextuale(RL, LCC).

preluare_lista_cuvinte_contextuale([S1, E1, E2, E3, E4, E5, S2 | RL], [[E1, E2, E3, E4, E5] | LCC]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_cheie5(E1, E2, E3, E4, E5),
    preluare_lista_cuvinte_contextuale(RL, LCC).

preluare_lista_cuvinte_contextuale([S1, E1, E2, E3, E4, S2 | RL], [[E1, E2, E3, E4] | LCC]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_cheie4(E1, E2, E3, E4),
    preluare_lista_cuvinte_contextuale(RL, LCC).

preluare_lista_cuvinte_contextuale([S1, E1, E2, E3, S2 | RL], [[E1, E2, E3] | LCC]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_cheie3(E1, E2, E3),
    preluare_lista_cuvinte_contextuale(RL, LCC).

preluare_lista_cuvinte_contextuale([S1, E1, E2, S2 | RL], [[E1, E2] | LCC]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_cheie2(E1, E2),
    preluare_lista_cuvinte_contextuale(RL, LCC).

preluare_lista_cuvinte_contextuale([_ | RL], LCC) :-
    preluare_lista_cuvinte_contextuale(RL, LCC).

% Predicat pentru a obtine o lista cu cuvintele rezervate.
preluare_lista_cuvinte_cheie([], []).

preluare_lista_cuvinte_cheie(['"' | RL], LCR) :-
    ignora_constanta_sir_caractere(RL, ListaDupaIgnorare),
    preluare_lista_cuvinte_cheie(ListaDupaIgnorare, LCR).

preluare_lista_cuvinte_cheie([S1, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, S2 | RL], [[E1, E2, E3, E4, E5, E6, E7, E8, E9, E10] | LCR]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_rezervat10(E1, E2, E3, E4, E5, E6, E7, E8, E9, E10),
    preluare_lista_cuvinte_cheie(RL, LCR).

preluare_lista_cuvinte_cheie([S1, E1, E2, E3, E4, E5, E6, E7, E8, E9, S2 | RL], [[E1, E2, E3, E4, E5, E6, E7, E8, E9] | LCR]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_rezervat9(E1, E2, E3, E4, E5, E6, E7, E8, E9),
    preluare_lista_cuvinte_cheie(RL, LCR).

preluare_lista_cuvinte_cheie([S1, E1, E2, E3, E4, E5, E6, E7, E8, S2 | RL], [[E1, E2, E3, E4, E5, E6, E7, E8] | LCR]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_rezervat8(E1, E2, E3, E4, E5, E6, E7, E8),
    preluare_lista_cuvinte_cheie(RL, LCR).

preluare_lista_cuvinte_cheie([S1, E1, E2, E3, E4, E5, E6, E7, S2 | RL], [[E1, E2, E3, E4, E5, E6, E7] | LCR]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_rezervat7(E1, E2, E3, E4, E5, E6, E7),
    preluare_lista_cuvinte_cheie(RL, LCR).

preluare_lista_cuvinte_cheie([S1, E1, E2, E3, E4, E5, E6, S2 | RL], [[E1, E2, E3, E4, E5, E6] | LCR]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_rezervat6(E1, E2, E3, E4, E5, E6),
    preluare_lista_cuvinte_cheie(RL, LCR).

preluare_lista_cuvinte_cheie([S1, E1, E2, E3, E4, E5, S2 | RL], [[E1, E2, E3, E4, E5] | LCR]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_rezervat5(E1, E2, E3, E4, E5),
    preluare_lista_cuvinte_cheie(RL, LCR).

preluare_lista_cuvinte_cheie([S1, E1, E2, E3, E4, S2 | RL], [[E1, E2, E3, E4] | LCR]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_rezervat4(E1, E2, E3, E4),
    preluare_lista_cuvinte_cheie(RL, LCR).

preluare_lista_cuvinte_cheie([S1, E1, E2, E3, S2 | RL], [[E1, E2, E3] | LCR]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_rezervat3(E1, E2, E3),
    preluare_lista_cuvinte_cheie(RL, LCR).

preluare_lista_cuvinte_cheie([S1, E1, E2, S2 | RL], [[E1, E2] | LCR]) :-
    (S1 = ' ' ; S1 = '\n'),
    (S2 = ' ' ; S2 = '\n'),
    este_cuvant_rezervat2(E1, E2),
    preluare_lista_cuvinte_cheie(RL, LCR).

preluare_lista_cuvinte_cheie([_ | RL], LCR) :-
    preluare_lista_cuvinte_cheie(RL, LCR).

% PREDICATE pentru a obtine o liste cu identificatori.

% Predicatul extrage identificatorii pentru Namespaces (librarii), clase si structuri.
preluare_lista_identificatori_ns_cl_st([], [], [], [], _).

preluare_lista_identificatori_ns_cl_st(['"' | RL], LCR) :-
    ignora_constanta_sir_caractere(RL, ListaDupaIgnorare),
    preluare_lista_identificatori_ns_cl_st(ListaDupaIgnorare, LCR).

% Primele doua predicate se ocupa de a extrage identificatorii de namespace (chiar si daca instructiunea este o ierarhie de namespace-uri).
preluare_lista_identificatori_ns_cl_st(['.' | RL], [Ident_NS | RLNS], LCL, LST, AltNS) :-
    AltNS = 1,
    extrage_identificator_namespace(RL, Ident_NS, ListaDupaExtragere, AltNS1),
    preluare_lista_identificatori_ns_cl_st(ListaDupaExtragere, RLNS, LCL, LST, AltNS1).

preluare_lista_identificatori_ns_cl_st(['u', 's', 'i', 'n', 'g', ' ' | RL], [Ident_NS | RLNS], LCL, LST, AltNS) :-
    AltNS = 0,
    extrage_identificator_namespace(RL, Ident_NS, ListaDupaExtragere, AltNS1),
    preluare_lista_identificatori_ns_cl_st(ListaDupaExtragere, RLNS, LCL, LST, AltNS1).

% Predicatul extrage identificatorii de clase
preluare_lista_identificatori_ns_cl_st(['c', 'l', 'a', 's', 's', ' ' | RL], LNS, [Ident_LCL | RLCL], LST, AltNS) :-
    extrage_identificator_clasa(RL, Ident_LCL, ListaDupaExtragere),
    preluare_lista_identificatori_ns_cl_st(ListaDupaExtragere, LNS, RLCL, LST, AltNS).

% Predicatul extrage identificatorii de structuri.
preluare_lista_identificatori_ns_cl_st(['s', 't', 'r', 'u', 'c', 't', ' ' | RL], LNS, LCL, [Ident_LST | RLST], AltNS) :-
    extrage_identificator_clasa(RL, Ident_LST, ListaDupaExtragere),
    preluare_lista_identificatori_ns_cl_st(ListaDupaExtragere, LNS, LCL, RLST, AltNS).

preluare_lista_identificatori_ns_cl_st([_ | RL], LNS, LCL, LST, AltNS) :- 
    preluare_lista_identificatori_ns_cl_st(RL, LNS, LCL, LST, AltNS).

extrage_identificator_namespace([], [], [], 0).
extrage_identificator_namespace([';' | RL], [], RL, 0).
extrage_identificator_namespace(['.' | RL], [], ['.' | RL], 1).
extrage_identificator_namespace([E | RL], [E | RLIden], LDE, AltNS) :- extrage_identificator_namespace(RL, RLIden, LDE, AltNS).

extrage_identificator_clasa([], [], []).
extrage_identificator_clasa(['\n' | RL], [], RL).
extrage_identificator_clasa([' ' | RL], [], RL).
extrage_identificator_clasa(['{' | RL], [], RL).
extrage_identificator_clasa([E | RL], [E | RLIden], LDE) :- extrage_identificator_clasa(RL, RLIden, LDE).

% Predicatul extrage identificatorii de variabile.
preluare_lista_identificatori_var([], []).

preluare_lista_identificatori_var(['"' | RL], LVAR) :-
    ignora_constanta_sir_caractere(RL, ListaDupaIgnorare),
    preluare_lista_identificatori_var(ListaDupaIgnorare, LVAR).

preluare_lista_identificatori_var([E | RL], [Var | RLVAR]) :-
    (este_litera_mica(E) ; este_litera_mare(E) ; este_underscore(E)),
    extrage_identificator_variabila(RL, Temp, ListaDupaExtragere),
    Var = [E | Temp],
    preluare_lista_identificatori_var(ListaDupaExtragere, RLVAR).

preluare_lista_identificatori_var([_ | RL], LVAR) :- preluare_lista_identificatori_var(RL, LVAR).

extrage_identificator_variabila([], [], []).
extrage_identificator_variabila(['(' | RL], ['('], RL).
extrage_identificator_variabila([E | RL], [], RL) :- \+ (este_litera_mica(E) ; este_litera_mare(E) ; este_underscore(E) ; este_numar(E)).
extrage_identificator_variabila([E | RL], [E | RLIden], LDE) :- extrage_identificator_variabila(RL, RLIden, LDE).

% Predicatul extrage identificatorii de metode.
preluare_lista_identificatori_metode([], []).
preluare_lista_identificatori_metode([E | RL], [Met | RLMET]) :-
    este_membru('(', E),
    extrage_identificator_metoda(E, Met),
    preluare_lista_identificatori_metode(RL, RLMET).
preluare_lista_identificatori_metode([E | RL], LMET) :- preluare_lista_identificatori_metode(RL, LMET).

extrage_identificator_metoda([], []).
extrage_identificator_metoda(['(' | RL], []).
extrage_identificator_metoda([E | RL], [E | RLIden]) :- extrage_identificator_metoda(RL, RLIden).

% /=====================/PREDICATE AJUTATOARE/=====================/

% Predicat pentru a elimina reaparitiile elementelor dintr-o lista.
elimina_elemente_duplicate_lista_de_liste([], []).
elimina_elemente_duplicate_lista_de_liste([E | LI], ListaFinala) :-
    este_membru_lista_de_liste(E, LI),
    elimina_elemente_duplicate_lista_de_liste(LI, ListaFinala).
elimina_elemente_duplicate_lista_de_liste([E | LI], [E | LF]) :-
    elimina_elemente_duplicate_lista_de_liste(LI, LF).

% Predicatul elimina cuvintele cheie, contextuale etc.
/*elimina_elemente_neidentificatori([], [], []).
elimina_elemente_neidentificatori([E | RL], LI, LF) :-
    elimina_element(E, LI, LF),
    elimina_elemente_neidentificatori(RL, LI, LF).
elimina_elemente_neidentificatori([E | RL], LI, LF) :- elimina_elemente_neidentificatori(RL, LI, LF).

elimina_element(_, [], []).
elimina_element(E, [E1 | RLI], [E1 | RLF]) :-
    E \= E1,
    elimina_element(E, RLI, RLF).
elimina_element(E, [E1 | RLI], LF) :- elimina_element(E, RLI, LF).*/


este_membru_lista_de_liste([], []).
este_membru_lista_de_liste(L, [L | _]).
este_membru_lista_de_liste(L, [_ | RL]) :- este_membru_lista_de_liste(L, RL).

adauga_element(E, L, [E|L]).

% Predicat pentru afisarea unei liste, fiecare element aflat una sub alta.
afisare_lista([]).
afisare_lista([E | RL]) :- writeln(E), afisare_lista(RL).

% Predicat pentru afisarea unei liste de liste (sir de caractere)
afisare_lista_de_liste([]).
afisare_lista_de_liste([E | RL]) :-
    afisare_lista_carac(E),
    write('\n'),
    afisare_lista_de_liste(RL).

afisare_lista_carac([]).
afisare_lista_carac([E | RL]) :-
    write(E),
    afisare_lista_carac(RL).
afisare_lista_carac([_ | RL]) :- afisare_lista_carac(RL).

ignora_constanta_sir_caractere([], []).
ignora_constanta_sir_caractere(['"' | RL], RL).
ignora_constanta_sir_caractere([_ | RL], ListaDupaIgnorare) :- ignora_constanta_sir_caractere(RL, ListaDupaIgnorare).

% Predicatul ignora cifrele gasite intr-un identificator. Se foloseste in predicatul preluare_lista_constante_numerice.
ignora_cifre_identificator([], []).
ignora_cifre_identificator([E | RL], [E | RL]) :- \+ este_numar(E).
ignora_cifre_identificator([_ | RL], ListaDupaIgnorare) :- ignora_cifre_identificator(RL, ListaDupaIgnorare).

elimina_spatii_albe([], []).
elimina_spatii_albe([' ' | RLI], LF) :- elimina_spatii_albe(RLI, LF).
elimina_spatii_albe([E | RLI], [E | RLF]) :- elimina_spatii_albe(RLI, RLF).

este_membru(E, [E | _]).
este_membru(E,[_ | RL]) :- este_membru(E, RL).

concatenare(L,[],L).
concatenare([],L,L).
concatenare([NR1|L1],L2,[NR1|R]):-concatenare(L1,L2,R).

este_litera_mica('a').
este_litera_mica('b').
este_litera_mica('c').
este_litera_mica('d').
este_litera_mica('e').
este_litera_mica('f').
este_litera_mica('g').
este_litera_mica('h').
este_litera_mica('i').
este_litera_mica('j').
este_litera_mica('k').
este_litera_mica('l').
este_litera_mica('m').
este_litera_mica('n').
este_litera_mica('o').
este_litera_mica('p').
este_litera_mica('q').
este_litera_mica('r').
este_litera_mica('s').
este_litera_mica('t').
este_litera_mica('u').
este_litera_mica('v').
este_litera_mica('w').
este_litera_mica('x').
este_litera_mica('y').
este_litera_mica('z').

este_litera_mare('A').
este_litera_mare('B').
este_litera_mare('C').
este_litera_mare('D').
este_litera_mare('E').
este_litera_mare('F').
este_litera_mare('G').
este_litera_mare('H').
este_litera_mare('I').
este_litera_mare('J').
este_litera_mare('K').
este_litera_mare('L').
este_litera_mare('M').
este_litera_mare('N').
este_litera_mare('O').
este_litera_mare('P').
este_litera_mare('Q').
este_litera_mare('R').
este_litera_mare('S').
este_litera_mare('T').
este_litera_mare('U').
este_litera_mare('V').
este_litera_mare('W').
este_litera_mare('X').
este_litera_mare('Y').
este_litera_mare('Z').

este_underscore('_').

este_numar('0').
este_numar('1').
este_numar('2').
este_numar('3').
este_numar('4').
este_numar('5').
este_numar('6').
este_numar('7').
este_numar('8').
este_numar('9').

este_separator('.').
este_separator(',').
este_separator(';').
este_separator('{').
este_separator('}').
este_separator('(').
este_separator(')').
este_separator('[').
este_separator(']').
este_separator(':').
este_separator('#').
este_separator2('=', '>').
este_separator2(':', ':').

este_operator('*').
este_operator('/').
este_operator('%').
este_operator('+').
este_operator('-').
este_operator('<').
este_operator('>').
este_operator('!').
este_operator('&').
este_operator('|').
este_operator('^').
este_operator('~').
este_operator2('+', '+').
este_operator2('-', '-').
este_operator2('+', '=').
este_operator2('-', '=').
este_operator2('<', '=').
este_operator2('>', '=').
este_operator2('&', '&').
este_operator2('|', '|').
este_operator2('<', '<').
este_operator2('>', '>').
este_operator2('=', '=').
este_operator2('!', '=').
este_operator2('=', '>').
este_operator3('>', '>', '>').

este_cuvant_cheie2('b', 'y').
este_cuvant_cheie2('o', 'n').
este_cuvant_cheie2('o', 'r').
este_cuvant_cheie3('a', 'd', 'd').
este_cuvant_cheie3('a', 'n', 'd').
este_cuvant_cheie3('g', 'e', 't').
este_cuvant_cheie3('l', 'e', 't').
este_cuvant_cheie3('n', 'o', 't').
este_cuvant_cheie3('s', 'e', 't').
este_cuvant_cheie3('v', 'a', 'r').
este_cuvant_cheie4('a', 'r', 'g', 's').
este_cuvant_cheie4('f', 'i', 'l', 'e').
este_cuvant_cheie4('f', 'r', 'o', 'm').
este_cuvant_cheie4('i', 'n', 'i', 't').
este_cuvant_cheie4('i', 'n', 't', 'o').
este_cuvant_cheie4('j', 'o', 'i', 'n').
este_cuvant_cheie4('n', 'i', 'n', 't').
este_cuvant_cheie4('w', 'i', 't', 'h').
este_cuvant_cheie4('w', 'h', 'e', 'n').
este_cuvant_cheie5('a', 'l', 'i', 'a', 's').
este_cuvant_cheie5('a', 's', 'y', 'n', 'c').
este_cuvant_cheie5('a', 'w', 'a', 'i', 't').
este_cuvant_cheie5('f', 'i', 'e', 'l', 'd').
este_cuvant_cheie5('g', 'r', 'o', 'u', 'p').
este_cuvant_cheie5('n', 'u', 'i', 'n', 't').
este_cuvant_cheie5('v', 'a', 'l', 'u', 'e').
este_cuvant_cheie5('y', 'i', 'e', 'l', 'd').
este_cuvant_cheie5('w', 'h', 'e', 'r', 'e').
este_cuvant_cheie5('w', 'h', 'e', 'r', 'e').
este_cuvant_cheie6('a', 'l', 'l', 'o', 'w', 's').
este_cuvant_cheie6('e', 'q', 'u', 'a', 'l', 's').
este_cuvant_cheie6('g', 'l', 'o', 'b', 'a', 'l').
este_cuvant_cheie6('n', 'a', 'm', 'e', 'o', 'f').
este_cuvant_cheie6('r', 'e', 'c', 'o', 'r', 'd').
este_cuvant_cheie6('r', 'e', 'm', 'o', 'v', 'e').
este_cuvant_cheie6('s', 'c', 'o', 'p', 'e', 'd').
este_cuvant_cheie6('s', 'e', 'l', 'e', 'c', 't').
este_cuvant_cheie7('d', 'y', 'n', 'a', 'm', 'i', 'c').
este_cuvant_cheie7('n', 'o', 't', 'n', 'u', 'l', 'l').
este_cuvant_cheie7('o', 'r', 'd', 'e', 'r', 'b', 'y').
este_cuvant_cheie7('p', 'a', 'r', 't', 'i', 'a', 'l').
este_cuvant_cheie7('p', 'a', 'r', 't', 'i', 'a', 'l').
este_cuvant_cheie7('m', 'a', 'n', 'a', 'g', 'e', 'd').
este_cuvant_cheie8('r', 'e', 'q', 'u', 'i', 'r', 'e', 'd').
este_cuvant_cheie9('a', 's', 'c', 'e', 'n', 'd', 'i', 'n', 'g').
este_cuvant_cheie9('u', 'n', 'm', 'a', 'n', 'a', 'g', 'e', 'd').
este_cuvant_cheie9('u', 'n', 'm', 'a', 'n', 'a', 'g', 'e', 'd').
este_cuvant_cheie10('d', 'e', 's', 'c', 'e', 'n', 'd', 'i', 'n', 'g').

este_cuvant_rezervat2('a', 's').
este_cuvant_rezervat2('d', 'o').
este_cuvant_rezervat2('i', 'f').
este_cuvant_rezervat2('i', 'n').
este_cuvant_rezervat2('i', 's').
este_cuvant_rezervat3('f', 'o', 'r').
este_cuvant_rezervat3('i', 'n', 't').
este_cuvant_rezervat3('n', 'e', 'w').
este_cuvant_rezervat3('o', 'u', 't').
este_cuvant_rezervat3('r', 'e', 'f').
este_cuvant_rezervat3('t', 'r', 'y').
este_cuvant_rezervat4('b', 'a', 's', 'e').
este_cuvant_rezervat4('b', 'o', 'o', 'l').
este_cuvant_rezervat4('b', 'y', 't', 'e').
este_cuvant_rezervat4('c', 'a', 's', 'e').
este_cuvant_rezervat4('c', 'h', 'a', 'r').
este_cuvant_rezervat4('e', 'l', 's', 'e').
este_cuvant_rezervat4('e', 'n', 'u', 'm').
este_cuvant_rezervat4('g', 'o', 't', 'o').
este_cuvant_rezervat4('l', 'o', 'c', 'k').
este_cuvant_rezervat4('l', 'o', 'n', 'g').
este_cuvant_rezervat4('n', 'u', 'l', 'l').
este_cuvant_rezervat4('t', 'h', 'i', 's').
este_cuvant_rezervat4('t', 'r', 'u', 'e').
este_cuvant_rezervat4('u', 'i', 'n', 't').
este_cuvant_rezervat4('v', 'o', 'i', 'd').
este_cuvant_rezervat5('b', 'r', 'e', 'a', 'k').
este_cuvant_rezervat5('c', 'a', 't', 'c', 'h').
este_cuvant_rezervat5('c', 'l', 'a', 's', 's').
este_cuvant_rezervat5('c', 'o', 'n', 's', 't').
este_cuvant_rezervat5('e', 'v', 'e', 'n', 't').
este_cuvant_rezervat5('f', 'a', 'l', 's', 'e').
este_cuvant_rezervat5('f', 'i', 'x', 'e', 'd').
este_cuvant_rezervat5('f', 'l', 'o', 'a', 't').
este_cuvant_rezervat5('s', 'b', 'y', 't', 'e').
este_cuvant_rezervat5('s', 'h', 'o', 'r', 't').
este_cuvant_rezervat5('t', 'h', 'r', 'o', 'w').
este_cuvant_rezervat5('u', 'l', 'o', 'n', 'g').
este_cuvant_rezervat5('u', 's', 'i', 'n', 'g').
este_cuvant_rezervat5('w', 'h', 'i', 'l', 'e').
este_cuvant_rezervat6('d', 'o', 'u', 'b', 'l', 'e').
este_cuvant_rezervat6('e', 'x', 't', 'e', 'r', 'n').
este_cuvant_rezervat6('o', 'b', 'j', 'e', 'c', 't').
este_cuvant_rezervat6('p', 'a', 'r', 'a', 'm', 's').
este_cuvant_rezervat6('p', 'u', 'b', 'l', 'i', 'c').
este_cuvant_rezervat6('r', 'e', 't', 'u', 'r', 'n').
este_cuvant_rezervat6('s', 'e', 'a', 'l', 'e', 'd').
este_cuvant_rezervat6('s', 'i', 'z', 'e', 'o', 'f').
este_cuvant_rezervat6('s', 't', 'a', 't', 'i', 'c').
este_cuvant_rezervat6('s', 't', 'r', 'i', 'n', 'g').
este_cuvant_rezervat6('s', 't', 'r', 'u', 'c', 't').
este_cuvant_rezervat6('s', 'w', 'i', 't', 'c', 'h').
este_cuvant_rezervat6('t', 'y', 'p', 'e', 'o', 'f').
este_cuvant_rezervat6('u', 'n', 's', 'a', 'f', 'e').
este_cuvant_rezervat6('u', 's', 'h', 'o', 'r', 't').
este_cuvant_rezervat7('c', 'h', 'e', 'c', 'k', 'e', 'd').
este_cuvant_rezervat7('d', 'e', 'c', 'i', 'm', 'a', 'l').
este_cuvant_rezervat7('d', 'e', 'f', 'a', 'u', 'l', 't').
este_cuvant_rezervat7('f', 'i', 'n', 'a', 'l', 'l', 'y').
este_cuvant_rezervat7('f', 'o', 'r', 'e', 'a', 'c', 'h').
este_cuvant_rezervat7('p', 'r', 'i', 'v', 'a', 't', 'e').
este_cuvant_rezervat7('v', 'i', 'r', 't', 'u', 'a', 'l').
este_cuvant_rezervat8('a', 'b', 's', 't', 'r', 'a', 'c', 't').
este_cuvant_rezervat8('c', 'o', 'n', 't', 'i', 'n', 'u', 'e').
este_cuvant_rezervat8('d', 'e', 'l', 'e', 'g', 'a', 't', 'e').
este_cuvant_rezervat8('e', 'x', 'p', 'l', 'i', 'c', 'i', 't').
este_cuvant_rezervat8('i', 'm', 'p', 'l', 'i', 'c', 'i', 't').
este_cuvant_rezervat8('i', 'n', 't', 'e', 'r', 'n', 'a', 'l').
este_cuvant_rezervat8('o', 'p', 'e', 'r', 'a', 't', 'o', 'r').
este_cuvant_rezervat8('o', 'v', 'e', 'r', 'r', 'i', 'd', 'e').
este_cuvant_rezervat8('r', 'e', 'a', 'd', 'o', 'n', 'l', 'y').
este_cuvant_rezervat8('v', 'o', 'l', 'a', 't', 'i', 'l', 'e').
este_cuvant_rezervat9('i', 'n', 't', 'e', 'r', 'f', 'a', 'c', 'e').
este_cuvant_rezervat9('n', 'a', 'm', 'e', 's', 'p', 'a', 'c', 'e').
este_cuvant_rezervat9('p', 'r', 'o', 't', 'e', 'c', 't', 'e', 'd').
este_cuvant_rezervat9('u', 'n', 'c', 'h', 'e', 'c', 'k', 'e', 'd').
este_cuvant_rezervat10('s', 't', 'a', 'c', 'k', 'a', 'l', 'l', 'o', 'c').