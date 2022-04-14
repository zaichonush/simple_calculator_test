
/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

/* ЗАВДАННЯ
Консольный калькулятор которы может: принять на вход выражение вида 
<value1> <operation> <value2>, где value(1,2) это целые числа, 
а operation это мат.операции {+,-./,*,^,mod, %, sqrt}, 
и выдать результат вычисления в консоль. 
После выдачи ответа - должен быть готов принять следующее выражение.
*/

// ВВЕДЕМО ПРИПУЩЕННЯ/ОБМЕЖЕННЯ  
// аналіз поставленої задачі показує, що формат <value1> <operation> <value2>
// не придатний для операції модуля і добуття кореня - mod, sqrt
// тому потрібно призначити допустимий формат вводу даних.
// 1. обмежимося допустимим діапазоном вхідного повідомлення 10 символів
// 2. операції +,-,/,*,^, % робимо з числами до 5 розрядів 
// тобто, наприклад,   1111+1111, 11+11111, 111+11111, 1111+11, 
// 11111+1, без пробілів. (111111+11 - програма видасть некоректний результат, ПЕРЕВІРКА, наразі, не робиться) 
// другий операнд може бути лише додатним. ділити, 
// множити на від'ємне число, а також підносити до від'ємного степеня не можна, 
// тобто формат запису a*(-b) не підтримується

// 3. операція модуля - не більше 5розрядного числа: mod(11111)
// 4. операція добування кореня - не більше 4розрядного числа: sqrt(1111),
// 5. "После выдачи ответа - должен быть готов принять следующее выражение." - 
// умову ДОПОВНЕНО можливістю продовжити роботу або вийти з програми 
// за бажанням користувача. для цього потрібно натиснути відповідні клавіші - 
// "c" - щоб продовжити, "q" - для виходу з програми і кнопку ENTER

// для всіх операцій виконується ПЕРЕВІРКА: 
// - чи немає, часом, недозволених символів, наприклад букв,
// - також перевірка на максимальну кількість введених символів,
//   наразі не більше 10
// - операція sqrt перевіряється на предмет від'ємного аргументу
// - операції mod і sqrt перевіряється на коректність вводу (але не 
//   перевіряється закриваюча дужка)

// зроблено і перевірено тут - https://www.onlinegdb.com/online_c_compiler, для С

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <conio.h>

#define INPUT_LENGTH 10 // mod(11111), sqrt(1111)

char input[INPUT_LENGTH];
int input_length = 0;
int control_key;
int continue_operation = 1;
int too_long_expression_flag = 0;

void fill_array_with_something(void);
int calculate(int first_number, char sign, int second_number);
int get_a_number( int digits, int start_index );

void plus_minus_operation(void);

void mod_operation(void);
void sqrt_operation(void);
void ahtung_message(void);


int main()
{
    printf("---- Console simple calculator ---- \n");
    fill_array_with_something();
    
// потім треба буде зациклить 
    while ( continue_operation )  
    {
        printf("Please, enter expression (< 4-digit number >< +,-,*,/,%,^ >< 4-digit number >)   \n");
        printf("or mod(< 5-digit number >)  \n");
        printf("or sqrt(< 4-digit number >)  \n");
        printf("---> ");
        
        scanf("%s" , input);
        
        input_length = strlen(input);
        //   перевірка на максимально допустиму довжину вхідної строчки
        if ( input_length > 10 ) // поки не перевіряєм
        {   
            too_long_expression_flag = 1;
        }
        else
        { too_long_expression_flag = 0; }
        
        printf("your expression is: %s \n", input);
        
        // показать що прийшло, відладка
      /*for ( int i = 0; i < input_length; i++ )
        {
             printf("input[%d] = %c,  int num = %d \n", i, input[i], (int)(input[i])   );
        }
        */
        
        // визначаємо яка в нас операція - над двома числами (+-/*^%), чи над одним (mod(), sqrt() )
        int operation;
        operation = (int)(input[0]);
        if ( (operation >= 48 )  && ( operation <= 57   ) || ( operation == 45 ) )
        {   operation = 1;  }
        
        if ( too_long_expression_flag == 1 )
        { operation = 2; }
        
        switch ( operation )
        {
            case 109: // 'm' - 109
                mod_operation();
            break;
            
            case 115: // 's' - 115
                sqrt_operation();
            break;
          
            case 1: // +-/*^%
                plus_minus_operation();
            break;
            
            case 2:
                printf("ERROR: too long expression: \n"); 
            break;
            
            default:
                ahtung_message(); 
            break;
            
        } // end of switch ( operation )
        
        printf("Would you like to continue <c> or quit <q> ?\n");
        printf("Press the button and then ENTER\n");
        fill_array_with_something();
        if ( getchar() == 'c' )
        { continue_operation = 1; }
        else if ( getchar() == 'q' )
        { continue_operation = 0; }

    } // end of while ( continue_operation )

    return 0;
} // end of int main()


/////////////////////////////////////////////////////////////
// functions

void fill_array_with_something(void)
{
    for ( int i = 0; i < INPUT_LENGTH; i++ )
    {
        input[i] = '#';
    }
}
// безпосередньо математична операція з числами
int calculate(int first_number, char sign, int second_number)
{
    int result;
    switch (sign)     // % - 37, * - 42, + - 43, - - 45, / - 47 , ^ - 94
    {
        case 37:
            result = first_number % second_number;
        break;
        
        case 42:
            result = first_number * second_number;
        break;
        
        case 43:
            result = first_number + second_number;
        break;
        
        case 45:
            result = first_number - second_number;
        break;
        
        case 47:
            result = first_number / second_number;
        break;
        
        case 94:
            result = 1;
            for ( int i = 0; i < second_number; i++ )
            {
                result = result * first_number; 
            }
        break;
    }
    return result;
} /// end of int calculate(int first_number, char sign, int second_number)

// у вхідному масиві лежить перше число, потім знак, потім друге число
// щоб ці числа дістать, потрібно знати розрядність числа (digits) і 
// індекс старшого розряду в масиві (start_index). тому у функцію передаємо ці значення
int get_a_number( int digits, int start_index )
{
    int result;
    switch (digits)
    {
        case 5:
            result = 10000 * (input[start_index + 0] - 48) +  1000 * (input[start_index + 1] - 48) + 100 * (input[start_index + 2] - 48) + 10 * (input[start_index + 3] - 48) + (input[start_index + 4] - 48) ;
        break;
        
        case 4:
            result = 1000 * (input[start_index + 0] - 48) + 100 * (input[start_index + 1] - 48) + 10 * (input[start_index + 2] - 48) + (input[start_index + 3] - 48) ;
        break;
        
        case 3:
            result = 100 * (input[start_index + 0] - 48) + 10 * (input[start_index + 1] - 48) + (input[start_index + 2] - 48) ;
        break;
        
        case 2:
            result =  10 * (input[start_index + 0] - 48) + (input[start_index + 1] - 48) ;
        break;
        
        case 1:
            result =  input[start_index + 0] - 48;
        break;
        
    }
    return result;
} // end of int get_a_number( int digits, int start_index )

//////////////////////////////////////////////////////////////////////////////

// mod(11111),  допустима довжина вхідної строчки 10
void mod_operation(void)
{
    int cnt = 4;
    int digit = 0;
    int result = 0;
    int unresolved_symbol_flag = 0;
    // перевірка коректності запису
    // закриту дужку в кінці не перевіряєм. а нада було б((
    if ( (input[0] == 'm') && ( input[1] == 'o' ) && (input[2] == 'd') && (input[3] == '(') )
    {
        if ( input[4] == '-'  )
        { cnt++; }
        while( cnt < INPUT_LENGTH )
        {
            // скануємо вхідну строчку до символа ) і дістаємо  число
            if (  input[cnt] != ')'    )
            {
                if ( ( input[cnt] >= 48 )  && ( input[cnt] <= 57 )       ) // і дивимося чи дійсно число, а не літера
                {
                    digit++;
                }
                else
                {
                    unresolved_symbol_flag = 1;
                }
            }
            else {break;}
            cnt++;
        } // end of while( cnt < INPUT_LENGTH )
    }
    else    {   ahtung_message();   }
    
    if ( unresolved_symbol_flag == 0 )
    {
        //printf("mod-> digits are: %d \n", digit);
        int start_index = 4;    
        if ( input[4] == '-'  ) { start_index++; }
        
        int number = get_a_number( digit, start_index );
        if ( input[4] == '-'  )      { number = - number; }
        //printf("mod-> number is : %d \n", number);
        result = (int)(sqrt(number*number));
        printf("result is : %d \n", result);
    }
    else    {   ahtung_message();   }
} // end of void mod_operation(void);

/////////////////////////////////////////////////////////////////////////

// sqrt(1111),  допустима довжина вхідної строчки 10
void sqrt_operation(void)
{
    int cnt = 5;
    int digit = 0;
    float result = 0;
    int unresolved_symbol_flag = 0;
    // перевірка коректності запису
    // закриту дужку в кінці не перевіряєм. а нада було б((
    if ( (input[0] == 's') && ( input[1] == 'q' ) && (input[2] == 'r') && (input[3] == 't') && (input[4] == '(') )
    {
        if ( input[5] == '-'  )
        { cnt++; }
        while( cnt < INPUT_LENGTH )
        {
            // скануємо вхідну строчку до символа ) і дістаємо число
            if (  input[cnt] != ')'    )
            {
                if ( ( input[cnt] >= 48 )  && ( input[cnt] <= 57 )       ) // і дивимося чи дійсно число, а не літера
                {
                    digit++;
                }
                else
                {
                    unresolved_symbol_flag = 1;
                }
            }
            else {break;}
            cnt++;
        } // end of while( cnt < INPUT_LENGTH )
    }
    else    {   ahtung_message();   }
    
    if ( unresolved_symbol_flag == 0 )
    {
        //printf("sqrt-> digits are: %d \n", digit);
        int start_index = 5;    
        if ( input[5] == '-'  ) { start_index++; }
        
        int number = get_a_number( digit, start_index );
        if ( input[5] == '-'  )      
        { 
            printf("ERROR: need positive number \n");
        }
        else 
        {
            //printf("sqrt-> number is : %d \n", number);
            result = sqrt(number);
            printf("result is : %f \n", result);
        }
    }
    else { ahtung_message(); }
    
} // end of void sqrt_operation(void)

//////////////////////////////////////////////////////////////////////

void plus_minus_operation (void)
{
    int res;
    int cnt = 0;    
    int digits_first = 0;
    int digits_second = 0;
    int first_number = 0;
    int second_number = 0;
    int unresolved_symbol_flag = 0;
    
    // дістаємо числа і символи ASCII
    // % - 37, * - 42, + - 43, - - 45, / - 47 , ^ - 94

    //  перевірка на від'ємне число
    if ( input[0] == '-'  ) { cnt = 1; }
    while( cnt < INPUT_LENGTH )
    {
        // скануємо вхідну строчку до символа операції і дістаємо ПЕРШЕ число
        // потрібно визначить розрядність числа (digits_first) 
        // і початок старшого розряду у вхідному масиві (start_index)
        //
        if ( ( input[cnt] != 37 )  && ( input[cnt] != 42 ) && ( input[cnt] != 43 ) && ( input[cnt] != 45 ) && ( input[cnt] != 47 )  && ( input[cnt] != 94 )    )
        {
            if ( ( input[cnt] >= 48 )  && ( input[cnt] <= 57 )       ) // і дивимося чи дійсно число, а не літера
            {
                digits_first++;
            }
            else
            {
                unresolved_symbol_flag = 1;
            }
        }
        else {break;}
        
        cnt++;
    } // end of while( cnt < INPUT_LENGTH )
    //printf("first digits are: %d \n", digits_first);
    
    int start_index = 0;
    if ( input[0] == '-'  ) { start_index = 1; }
    first_number = get_a_number( digits_first, start_index );
    if ( input[0] == '-'  ) { first_number = -first_number; }
    //printf("first number is : %d \n", first_number);
    
    // дістаємо ЗНАК
    char sign;  
    sign = input[digits_first];
    if ( input[0] == '-'  ) { sign = input[digits_first + 1]; }
    //printf("sign is : %c \n", sign);
    
    // дістаємо ДРУГЕ число
    
    
    cnt = digits_first + 1;
    if ( input[0] == '-'  ) { cnt = digits_first + 2; } //  перевіркa на від'ємне ПЕРШЕ число, тому +2
    while( cnt < INPUT_LENGTH )
    {
        if ( ( input[cnt] >= 48 )  && ( input[cnt] <= 57 )       )
        {
            digits_second++;
        }
        else    {   break; }
        cnt++;
    } // end of while( cnt < INPUT_LENGTH )
    
    //printf("second digits are: %d \n", digits_second);

    start_index = digits_first + 1; 
    if ( input[0] == '-'  ) { start_index = digits_first + 2; }
    second_number = get_a_number( digits_second, start_index );

    //printf("second number is: %d \n", second_number);

    res = calculate(first_number, sign, second_number);

    if ( unresolved_symbol_flag == 0 )
    {
        printf("result  is: %d \n", res);
    }
    else    {   ahtung_message();   }
        
} // end of void plus_minus_operation (void)


void ahtung_message(void)
{
    printf("ERROR: unresolved symbol or input length, try again \n");
}












