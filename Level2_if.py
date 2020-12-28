# Step 1: No.1330

# test
ex = '1 2'
ex = '10 2'
ex = '5 5'
A, B = map(int, ex.split())

# submit
A,B = map(int, input().split())

if A > B:
    print('>')
elif A < B:
    print('<')
else:
    print('==')


# Step 2: No.9498
score = int(input())

if score >= 90 and score <= 100:
    print('A')
elif score >= 80 and score < 90:
    print('B')
elif score >= 70 and score < 80:
    print('C')
elif score >= 60 and score < 70:
    print('D')
else:
    print('F')


# Step 3: No.2753
year = int(input())

if (year % 4 == 0) and (year%100 != 0 or year%400 == 0):
    print('1')
else:
    print('0')
    
    
# Step 4: No.14681
x = int(input())
y = int(input())
          
if x > 0 and y > 0:
    print('1')
elif x < 0 and y > 0:
    print('2')
elif x < 0 and y < 0:
    print('3')
else:
    print('4')
    

# Step 4: No.2884
H,M = map(int, input().split())
if M >= 45:
    M = M - 45
    print(H,M)
elif H > 0 and M < 45:
    H = H-1
    M = M + 15
    print(H,M)
else:
    H = 23
    M = M + 15
    print(H,M)