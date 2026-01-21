import re


def infix_to_rpn_exact(expression):
    # 1. Definicja priorytetów i łączności
    # Wyższe liczba = wyższy priorytet
    # '-1' to minus unarny, '-2' to minus binarny (odejmowanie)
    precedence = {
        "(": 0,
        "+": 1,
        "-2": 1,
        "*": 2,
        "/": 2,
        ":": 2,
        "log": 3,  # Logarytm jako operator infiksowy (p log q)
        "^": 4,
        "sin": 5,
        "sqrt1": 5,
        "sqrt2": 5,
        "-1": 5,  # Funkcje i minus unarny
    }

    # Operatory prawostronne
    right_associative = {"^", "-1", "sin", "sqrt1", "sqrt2"}

    # 2. Tokenizacja (rozbicie napisu na listę symboli)
    # Wyłapujemy słowa (sin, log...), liczby oraz znaki specjalne
    expression = expression.replace(" ", "")
    # Dodajemy spacje wokół operatorów, żeby łatwo podzielić, ale chronimy słowa
    tokens = re.findall(r"[a-zA-Z][a-zA-Z0-9]*|\d+|[:+\-*/()^]", expression)

    output = []
    stack = []

    # Flaga do wykrywania minusa unarnego.
    # True na początku lub po operatorze/nawiasie otwierającym.
    expect_operand = True

    for token in tokens:
        # --- A. Obsługa argumentów (Liczby i Zmienne) ---
        if token.isalnum() and token not in precedence:
            output.append(token)
            expect_operand = False  # Po liczbie spodziewamy się operatora

        # --- B. Obsługa Funkcji (sin, sqrt1, sqrt2) ---
        elif token in ["sin", "sqrt1", "sqrt2"]:
            stack.append(token)
            expect_operand = True

        # --- C. Obsługa Nawiasów ---
        elif token == "(":
            stack.append(token)
            expect_operand = True
        elif token == ")":
            while stack and stack[-1] != "(":
                output.append(stack.pop())
            if stack:
                stack.pop()  # Zdejmij '('
            # Jeśli przed nawiasem była funkcja (np. sin(...)), zdejmij ją teraz
            if stack and stack[-1] in ["sin", "sqrt1", "sqrt2"]:
                output.append(stack.pop())
            expect_operand = False

        # --- D. Obsługa Operatorów ---
        else:
            # Specjalna obsługa minusa
            op_symbol = token
            if token == "-":
                if expect_operand:
                    op_symbol = "-1"  # Minus unarny
                else:
                    op_symbol = "-2"  # Minus binarny (odejmowanie)

            # Logika Stacji Rozrządowej
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

    # Opróżnianie stosu na koniec
    while stack:
        output.append(stack.pop())

    return " ".join(output)


# --- TESTOWANIE ---

# Wyrażenie z obrazka (z drobną korektą: dodano * między 5 a sqrt2,
# ponieważ w wyniku ONP na końcu jest mnożenie tych składników)
infix_expr = "((sin(a+3:b-2)*(x^(-(1/t))))/((sqrt1 d + p log q):-c))*(5 * sqrt2(r/3))"

result = infix_to_rpn_exact(infix_expr)

print(f"Wejście: {infix_expr}")
print(f"Wynik:   {result}")

# Weryfikacja ze wzorcem z obrazka
expected = (
    "a 3 b : + 2 -2 sin x 1 t / -1 ^ * d sqrt1 p q log + c -1 : / 5 r 3 / sqrt2 *"
)
print(f"Wzorzec: {expected}")
print(f"Zgodne?: {result == expected}")

