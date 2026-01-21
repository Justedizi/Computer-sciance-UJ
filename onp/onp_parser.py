import re


def infix_to_rpn_multi_arg(expression):
    # Definicja priorytetów
    precedence = {"+": 1, "-": 1, "*": 2, "/": 2, "^": 3}
    functions = {"cos", "sin", "log", "pow", "sqrt", "root", "min", "max"}

    # Rozszerzony tokenizator (obsługuje nazwy, liczby, operatory i przecinki)
    tokens = re.findall(r"[a-zA-Z_]\w*|\d+|[+\-*/()^,]", expression.replace(" ", ""))

    output = []
    stack = []

    for token in tokens:
        # 1. Liczba lub zmienna
        if token.isalnum() and token not in functions and token not in precedence:
            output.append(token)

        # 2. Nazwa funkcji
        elif token in functions:
            stack.append(token)

        # 3. Przecinek (separator argumentów)
        elif token == ",":
            while stack and stack[-1] != "(":
                output.append(stack.pop())
            if not stack:
                raise ValueError("Błąd: przecinek poza nawiasami funkcji.")

        # 4. Lewy nawias
        elif token == "(":
            stack.append(token)

        # 5. Prawy nawias
        elif token == ")":
            while stack and stack[-1] != "(":
                output.append(stack.pop())
            if not stack:
                raise ValueError("Błąd: niepasujące nawiasy.")
            stack.pop()  # Usuń '(' ze stosu

            # Jeśli nad nawiasem była funkcja, dodaj ją do wyjścia
            if stack and stack[-1] in functions:
                output.append(stack.pop())

        # 6. Operatory
        elif token in precedence:
            while (
                stack
                and stack[-1] != "("
                and stack[-1] in precedence
                and precedence[stack[-1]] >= precedence[token]
            ):
                output.append(stack.pop())
            stack.append(token)

    while stack:
        if stack[-1] == "(":
            raise ValueError("Błąd: niedomknięty nawias.")
        output.append(stack.pop())

    return " ".join(output)


# Przykład użycia z funkcją 3-argumentową
test_expr = "cos(a, b, c) * 5"
print(f"Infiks: {test_expr}")
print(f"ONP:    {infix_to_rpn_multi_arg(test_expr)}")
