def add_brackets_to_function_calls(file_path):
    def add_brackets(line, index=0, stack=[]):
        if index >= len(line):
            return ""

        if line[index] == '(':
            stack.append('(')
        elif line[index] == ')':
            if stack:
                stack.pop()
        elif line[index] == ',' and stack:
            return ',' + add_brackets(line, index + 1, stack)
        elif line[index].isalnum() and not stack:
            return '(' + line[index] + add_brackets(line, index + 1, ['('])
        else:
            return line[index] + add_brackets(line, index + 1, stack)

        return line[index] + add_brackets(line, index + 1, stack)

    with open(file_path, 'r') as file:
        lines = file.readlines()

    modified_lines = [add_brackets(line) for line in lines]

    return modified_lines

# Test the function with the given file
file_path = 'example1.txt'
modified_content = add_brackets_to_function_calls(file_path)

# Print the modified content
for line in modified_content:
    print(line, end='')
