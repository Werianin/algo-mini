def rev_polish(expression):
    PRECED = {'**':10,
              '*':9, '@':9, '/':9, '//':9, '%':9,
              '+':8, '-':8,
              '<<':7, '>>':7,
              '&':6,
              '^':5,
              '|':4,
              'in':3, 'not_in':3, 'is':3, 'is_not':3,
              '<':3, '<=':3, '>':3, '>=':3, '==':3, '!=':3,
              'not':2,
              'and':1,
              'or':0
              }

    ASSOC = {'**':'R', 'not':'R',
             '*':'L', '@':'L', '/':'L', '//':'L', '%':'L',
             '+':'L', '-':'L', '<<':'L', '>>':'L', '&':'L',
             '^':'L', '|':'L', 'in':'L', 'not_in':'L', 'is':'L',
             'is_not':'L', '<':'L', '<=':'L', '>':'L', '>=':'L',
             '==':'L', '!=':'L', 'and':'L', 'or':'L'
             }

    expression = expression.split()
    op_stack = []
    rpn = []
    for c in expression:
        if c.isdigit():
            rpn.append(c)
        elif c == '(':
            op_stack.append(c)
        elif c == ')':
            while op_stack and op_stack[-1] != '(':
                rpn.append(op_stack.pop())
            op_stack.pop()
        else:
            while (op_stack and op_stack[-1] != '(' and
                   (PRECED[c] < PRECED[op_stack[-1]] or
                   (PRECED[c] == PRECED[op_stack[-1]] and ASSOC[c] == 'L'))):
                rpn.append(op_stack.pop())
            op_stack.append(c)

    rpn.extend(op_stack)

    return ' '.join(rpn)

ex1 = "1 + 9 * ( 8 - 4 )"
ex2 = "( 4 + 2 ) * ( 1 - 4 ) / 8 ** 8 + ( 4 > 2 and 0 < 777 ) or ( 42 is 69 )"
rpn1 = rev_polish(ex1)
print(ex1)
print(rpn1)
print()
rpn2 = rev_polish(ex2)
print(ex2)
print(rpn2)
