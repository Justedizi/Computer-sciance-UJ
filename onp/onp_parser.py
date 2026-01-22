import re


def infix_to_rpn_ultimate(expression):
    # --- 1. KONFIGURACJA (PRIORYTETY I TYPY) ---

    # Słownik priorytetów (im wyższa liczba, tym ważniejsze działanie)
    # Zgodnie z zasadą ze slajdów: operatory o niższej krotności (unarne) mają wyższy priorytet.
    precedence = {
        "(": 0,
        "+": 1,
        "-2": 1,  # Dodawanie, Odejmowanie (binarne)
        "*": 2,
        "/": 2,
        ":": 2,  # Mnożenie, Dzielenie
        "log": 3,  # Logarytm jako operator infiksowy (a log b)
        "^": 4,  # Potęgowanie
        # Funkcje i operatory unarne (najwyższy priorytet)
        "-1": 5,  # Minus unarny (negacja)
        "sin": 5,
        "cos": 5,
        "ln": 5,
        "sqrt1": 5,
        "sqrt2": 5,
        "min": 5,
        "max": 5,
    }

    # Zbiór operatorów łącznych prawostronnie (dla potęgowania a^b^c -> a^(b^c))
    right_associative = {"^", "-1"}

    # Zbiór nazw, które traktujemy jak funkcje f(arg1, arg2...)
    functions = {"sin", "cos", "ln", "sqrt1", "sqrt2", "min", "max"}

    # --- 2. TOKENIZACJA (PODZIAŁ NA KAWAŁKI) ---
    # Usuwamy spacje i dzielimy napis na: słowa, liczby, lub znaki specjalne
    expression = expression.replace(" ", "")
    # Wzorzec wyłapuje: liczby, słowa (np. sin, a, log), oraz symbole operatorów
    tokens = re.findall(r"[a-zA-Z][a-zA-Z0-9]*|\d+|[:+\-*/()^,]", expression)

    output = []  # Kolejka wyjściowa (ONP)
    stack = []  # Stos operatorów

    # Flaga: czy spodziewamy się teraz liczby/argumentu?
    # True na początku, po '(', po przecinku i po operatorach.
    # Służy do odróżnienia minusa unarnego (-1) od binarnego (-2).
    expect_operand = True

    for token in tokens:
        # A. Jeśli to LICZBA lub ZMIENNA (ale nie nazwa funkcji ani operatora 'log')
        if token.isalnum() and token not in functions and token != "log":
            output.append(token)
            expect_operand = False  # Po liczbie spodziewamy się operatora

        # B. Jeśli to FUNKCJA (np. sin, min, ln, sqrt2)
        elif token in functions:
            stack.append(token)
            expect_operand = True  # Po nazwie funkcji spodziewamy się '('

        # C. Jeśli to PRZECINEK (separator argumentów w min/max/sqrt2)
        elif token == ",":
            # Zdejmujemy operatory aż do nawiasu '(' (ale go nie usuwamy)
            while stack and stack[-1] != "(":
                output.append(stack.pop())
            expect_operand = True  # Po przecinku musi być kolejny argument

        # D. Jeśli to LEWY NAWIAS
        elif token == "(":
            stack.append(token)
            expect_operand = True

        # E. Jeśli to PRAWY NAWIAS
        elif token == ")":
            # Zdejmuj wszystko do lewego nawiasu
            while stack and stack[-1] != "(":
                output.append(stack.pop())

            stack.pop()  # Usuń '(' ze stosu

            # Jeśli na szczycie stosu została funkcja (np. min, sin), zdejmij ją teraz
            if stack and stack[-1] in functions:
                output.append(stack.pop())

            expect_operand = False

        # F. Jeśli to OPERATOR (+, -, *, :, log, ^)
        else:
            op_symbol = token

            # Detekcja minusa:
            if token == "-":
                if expect_operand:
                    op_symbol = "-1"  # Unarny (negacja), bo spodziewaliśmy się liczby
                else:
                    op_symbol = "-2"  # Binarny (odejmowanie), bo była liczba wcześniej

            # Algorytm "Stacja Rozrządowa" (Shunting Yard)
            while (
                stack
                and stack[-1] != "("
                and (
                    precedence.get(stack[-1], 0) > precedence.get(op_symbol, 0)
                    or (
                        precedence.get(stack[-1], 0) == precedence.get(op_symbol, 0)
                        and op_symbol not in right_associative
                    )
                )
            ):
                output.append(stack.pop())

            stack.append(op_symbol)
            expect_operand = True

    # Na koniec opróżniamy stos
    while stack:
        output.append(stack.pop())

    return " ".join(output)


# --- TESTOWANIE ---

print("--- Test 1: Logarytm naturalny (unarny) i zwykły (operator) ---")
# ln(a) - funkcja, b log c - operator
expr1 = "ln(a) + b log c"
print(f"Wejście: {expr1}")
print(f"Wynik:   {infix_to_rpn_ultimate(expr1)}")
# Oczekiwane: a ln b c log +

print("\n--- Test 2: Funkcja min z 3 argumentami ---")
expr2 = "min(a, b, c) * max(x, y)"
print(f"Wejście: {expr2}")
print(f"Wynik:   {infix_to_rpn_ultimate(expr2)}")
# Oczekiwane: a b c min x y max *

print("\n--- Test 3: Skomplikowany wzór z wykładów (sqrt1, sqrt2, log) ---")
# Wzór z cosinusem i mianownikiem z pierwiastkami
expr3 = "cos(a)^(b:c) / ( sqrt1( log(d, (e/f)*(g*h)) / k ) + sqrt2(-(n-p), m) )"
print(f"Wejście: {expr3}")
print(f"Wynik:   {infix_to_rpn_ultimate(expr3)}")

print("\n--- Test 4: Mieszane minusy ---")
# -a to negacja (-1), b-c to odejmowanie (-2)
expr4 = "-a + (b - c)"
print(f"Wejście: {expr4}")
print(f"Wynik:   {infix_to_rpn_ultimate(expr4)}")
expr5 = "sqrt1(a) + b sqrt2(c)"
print(infix_to_rpn_ultimate(expr5))
# Oczekiwane: a -1 b c -2 +
