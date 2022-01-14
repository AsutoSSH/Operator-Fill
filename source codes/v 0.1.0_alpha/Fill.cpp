#include <iostream>
using namespace std;

typedef struct
{
    char type;
    int pos;
} op;

op *ops = (op*)malloc(50 * sizeof(op));

void DrawTitle();
string BlankMaker(string inp);
void DrawQues();
void Blankpos();
int Chck_inp();
int Process();
int redo_current_ques();
void randomgenerator();
void generatebckt(string inp);
void insertdiv(string inp);
double OmegaCalculate(string inp);
int Bckt_Sept(string inp);
bool Bckt_check(string inp);
double MultiCalculate(string inp);
double Calculate(double l, char op, double r);
void SeparateNumsnOps(string inp);

int *bckt = (int*)malloc(2 * sizeof(int));							//STORES POSN OF CURRENT BRACKET PAIR
int *blankpos = (int*)malloc(15 * sizeof(int));						//STORES THE POSN OF BLANKS('_') PRESENT IN BLANKGEN STRING
int bckt_count = 0, num_count = 0, op_count = 0, qno = 1, chck_inp, crct_ans_count = 0;
int lenfactor, valuefactor;                                         //LENGTH FACTOR AND MAX VALUE FACTOR MODIFIED BY SET_DIFFICULTY() AND USED BY RANDOMGENERATOR()
int j = 0;                                                          //THIS IS A POINTER FOR BLANKPOS() WHICH IS ALSO ACCESSED BY PROCESS() HENCE I HAD TO MAKE IT GLOBAL
double *nums = (double*)malloc(50 * sizeof(double));                //THIS STORES THE NUMERALS OF THE EQUATION
double ans, usrans;                                                 //ANS IS ACTUAL VALUE OF EQN WHILE USRANS IS THE RESULT OF USER'S EQUATION
bool will_to_play = 1;                                              //IT DOES WHAT IT SAYS MEASURES THE PLAYER'S WILL TO PLAY ;)
string generated, blankgen, input, usreqn;							//GENERATED: STORES THE RANDOMLY GENERATED ARITHMETIC  // BLANKGEN:STORES THE ARITHMETIC BUT WITH BLANKS INSTEAD OF OPERATORS //INPUT:STORES USER'S INPUT //USREQN: STORES THE EQUATION MADE USING USER'S INPUT

int main()
{
    DrawTitle();
    while (will_to_play != 0)
    {
        
        DrawQues();
        Blankpos();
        chck_inp = Chck_inp();
        if (chck_inp == 1)
        {
            Process();
            
        }
        else if (chck_inp == 2)
        {
            while (Chck_inp() == 2)
            {
                j = 0;
                cout << "An answer was: " << generated << ". Better Luck Next Question" << endl;
                DrawQues();
                Blankpos();
                if (Chck_inp() == 1)
                {
                    Process();    
                }
            }
        }
        j = 0;
    }
    cout << "You Answered " << crct_ans_count << " out of " << qno - 2 << " questions" << endl
         << "Press Ctrl+C to exit :)" << endl;

    getline(cin,input);
}

void DrawTitle()
{
    int qno =  1;
    cout << '\n' << "       WELCOME TO OPERATOR FILL    " << '\n'
    <<              "           MADE WITH C++           " << '\n'
    <<              "                   -BY ASHUTOSH MISHRA" << '\n' << '\n';
}

string BlankMaker(string inp)
{
    int len = inp.length();
    for (int i = 0; i < len; i++)
    {
        if (isdigit(inp[i]) == 0)
        {
            if (isdigit(inp[i+1]) == 0 && i+1 < len)
            {
                inp.replace(i,2,"_");
                len = inp.length();
            }
            else
            {
                inp.replace(i,1,"_");
            }
        }
    }
    len = inp.length();
    if (inp[len-1] == '_')
    {
        inp.replace(len-1,1,"..");
    }
    else
    {
        inp = inp + "..";
    }
    return inp;
}

void DrawQues()
{
    randomgenerator();
    blankgen = BlankMaker(generated);
    ans = OmegaCalculate(generated);
    cout << "Question " << qno << ": " << blankgen << " = " << ans <<'\n' <<
            "Enter Answer: ";
    input.erase();
    getline(cin,input);
    qno++;
}

void Blankpos()
{
    for (int i = 0; i < blankgen.length(); i++)
    {
        if (blankgen[i] == '_')
        {
            blankpos[j] = i;
            j++;
        }
    }
    blankpos[j] = blankgen.length() - 2;
    
}

int Chck_inp()
{
    if (input == "end" || input == "End" || input == "END")
    {
        will_to_play = 0;
        return 4;
    }
    else if (input == "skip" || input == "Skip" || input == "SKIP")
    {
        return 2;
    }
    else if (input == "")
    {
        cout << "If you want to skip this question use 'skip'(without quotes). Dont leave input blank." << endl;
        redo_current_ques();
        return 3;
    }
    else
    {
        int chck = 0;
        for (int i = 0; i < input.length(); i++)
        {
            switch (input[i])
            {
            case '+':
                chck++;
                break;
            case '-':
                chck++;
                break;
            case '*':
                chck++;
                break;
            case '/':
                chck++;
                break;
            case '(':
                chck++;
                break;
            case ')':
                chck++;
                break;
            case ' ':
                chck++;
                break;                
            }
        }

        if (chck < input.length())
        {
            cout << "INVALID INPUT" << endl;
            redo_current_ques();
            return 0;
        }
        else
        {
            return 1;
        }
    }
    return 1;
}

int Process()
{
    bool approval = 0;
    usreqn = blankgen;
    string tmp;
    int k = 0, shft_fact = 0;
    for (int q = 0; q < input.length(); q++)
    {
        for (int i = 0 + q; input[i] != ' ' && i < input.length(); i++)
        {
            tmp += input[i];
            q = i;
        }
        if (k < j)
        {
            if (tmp.length() <= 2)
            {
                if (tmp.length() == 1)
                {
                    if (tmp != ")")
                    {
                        usreqn.replace(blankpos[k] + shft_fact,1,tmp);
                        shft_fact = shft_fact + tmp.length() - 1;
                        k++;
                        q++;
                        tmp.erase();
                        approval = 1;
                    }
                    else
                    {
                        cout << "')' character only cant fill a compulsory blank. It must be followed by an operator." << endl;
                        approval = 0;
                        input.erase();  
                        redo_current_ques();
                        return 0;
                    }
                }
                else
                {
                    if (tmp[0] == '+' || tmp[0] == '-' || tmp[0] == '*' || tmp[0] == '/')
                    {
                        if (tmp[1] == '(')
                        {
                            usreqn.replace(blankpos[k] + shft_fact,1,tmp);
                            shft_fact = shft_fact + tmp.length() - 1;
                            k++;
                            q++;
                            tmp.erase();
                            approval = 1;
                        }
                        else
                        {
                            cout << "If Each blank has 2 characters and it starts with an operator then the 2nd character should be '(' only" << endl;
                            approval = 0;
                            input.erase();  
                            redo_current_ques();
                            return 0;
                        }
                    }
                    else if (tmp[0] == ')')
                    {
                        if (tmp[1] == '+' || tmp[1] == '-' || tmp[1] == '*' || tmp[1] == '/')
                        {
                            usreqn.replace(blankpos[k] + shft_fact,1,tmp);
                            shft_fact = shft_fact + tmp.length() - 1;
                            k++;
                            q++;
                            tmp.erase();
                            approval = 1;        
                        }
                        else
                        {
                            cout << "If a compulsory blank has 2 characters and it starts with ')' then the next charater should be an operator." << endl;
                            approval = 0;
                            input.erase();  
                            redo_current_ques();
                            return 0;
                        }        
                    }
                }
            }
            else 
            {
                cout << "There Should be No more than 2 characters for each blank" << endl;
                approval = 0;
                input.erase();  
                redo_current_ques();
                return 0;
            }
        }
        else
        {
            if (tmp == ")")
            {
                usreqn.replace(blankpos[k] + shft_fact, 2 , tmp);
                approval = 1;
            }
            else
            {
                cout << "The .. place only accepts ')' but you have assigned it to be '" << tmp << "' Please Enter only ')' for that place" << endl << endl;
                approval = 0;
                input.erase();  
                redo_current_ques();
                return 0;
            }
        }
    }
    int stray_bckt = 0;
    for (int i = 0; i < usreqn.length(); i++)
    {
        if (usreqn[i] == '_')
        {
            cout << "All compulsory blanks must be filled." << endl;
            approval = 0;
            input.erase();  
            redo_current_ques();
            return 0;
        }
        if (usreqn[i] == '(')
        {
            stray_bckt++;
        }
        if (usreqn[i] == ')')
        {
            stray_bckt--;
        }
    }
    if (stray_bckt != 0)
        {
            cout << "Please make sure for every '(' there is a ')' in your answer" << endl;
            approval = 0;
            input.erase();
            stray_bckt = 0;  
            redo_current_ques();
            return 0;
        }
    // CHECKING ANSWER
    if (approval = 1)
    {
        usrans = OmegaCalculate(usreqn);
        if (usrans == ans)
        {
            cout << '\n' << "Correct Answer +1 ;)" << endl << endl;
            crct_ans_count++;
        }
        else 
        {
            cout << '\n' << "Wrong Answer :(" << endl << "A correct ans was: " << generated << " while your ans was: " << usreqn << " which is equal to: " << usrans << endl << endl;
        }
        usrans = 0;
        ans = 0;
    }   
    return 0;
}

int redo_current_ques()
{
    cout << "Question " << qno - 1 << ": " << blankgen << " = " << ans << '\n' <<
            "Enter Answer: ";
    input.erase();
    usreqn.erase();
    getline(cin,input);
    chck_inp = Chck_inp();
    if (chck_inp == 1)
    {
        Process();
        j = 0;
        return 0;  
    }
    else
    {
        while (Chck_inp() == 2)
        {
            j = 0;
            cout << "An answer was: " << generated << ". Better Luck Next Question" << endl;
            DrawQues();
            Blankpos();
            if (Chck_inp() == 1)
            {
                Process();
                j = 0;
            }
        }
    }
    j = 0;
    return 0;
}

void randomgenerator()
{
    generated.erase();
    lenfactor = 1;
    valuefactor = 15;
    string nums, ops;
    int seed = 0;
    string op = "+-*+*--+";
    for (int i = 0; i < lenfactor; i++)
    {
        srand(time(0) + seed + time(NULL));
        nums = to_string(rand() % valuefactor + 1);
        seed = stoi(nums);
        ops = op[rand() % op.length()];
        generated = generated + nums + ops;
    }
    srand(time(0) + stoi(nums));
    nums = to_string(rand() % 20 + 1);
    generated = generated + nums;
    if((rand()%11)%2 == 0)
    {
        insertdiv(generated);
        if (lenfactor > 3)
        {
            insertdiv(generated);
            for (int i = 0; i < 2; i++)
            {
                for (int i = generated.length()-1; i > 0; i--)
                {
                    if (isdigit(generated[i]) == 0)
                    {
                        generated.erase(i,generated.length()-i);
                        i = 0;
                    }
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < 2; i++)
        {
            srand(time(0) + seed + time(NULL));
            nums = to_string(rand() % valuefactor + 1);
            seed = stoi(nums);
            ops = op[rand() % 6];
            generated = generated + ops + nums;
        }
    }
    generatebckt(generated);
}

void generatebckt(string inp)
{
    int post[20], count = 0, bcktpos, p;
    for (int i = 0; i < inp.length(); i++)
    {
        if (isdigit(inp[i]) == 0 && inp[i] != '/')
        {
            post[count] = i;
            count++;
        }
    }
    
    srand(time(0));
    p = (rand() % count);
    bcktpos = post[p];
    inp.insert(bcktpos+1,"(");
    post[count] = inp.length()-1;
    count++;
    p = rand()%((count-1)-(p+1) + 1) + p+1;
    bcktpos = post[p];
    inp.insert(bcktpos+1,")");
    generated = inp;   
}

void insertdiv(string inp)
{
    int count = 0, divpos;
    int *validpos = (int*)malloc(30 * sizeof(int));
    int l,r,p;
    string op = "+-*";
    char opp; 
    string result;

    for (int i=0; i < inp.length(); i++)
    {
        if (isdigit(inp[i]) == 0)
        {
            validpos[count] = i;
            count++;
        }
    }
    validpos[count] = inp.length();
    count++;
    r = rand()%9 + 1;
    l = r * (0.5*((rand()%20) + 1));
    
    opp = op[rand()%3];
    result = opp + to_string(l) + "/" + to_string(r);
    p = rand()%count;
    divpos = validpos[p];

    inp.insert(divpos,result);
    generated = inp;
    free(validpos);
}

double OmegaCalculate(string inp)
{
    double result;
    if (Bckt_check(inp) == true)
    {
        while (Bckt_Sept(inp) == 0)
        {
            string nobckt_inp;
            nobckt_inp = inp.substr(bckt[0] + 1, bckt[1] - bckt[0] - 1);
            string r = to_string(MultiCalculate(nobckt_inp));
            inp.replace(bckt[0], (bckt[1]-bckt[0])+1, r);
        }
        result = MultiCalculate(inp);
    }
    bckt_count = 0;
    num_count = 0;
    op_count = 0;
    fill_n(nums,50,NULL);
    fill_n(bckt,2,NULL);
    return result;
}

bool Bckt_check(string inp)
{
    int stray_bckt = 0;
    for (int i = 0; i < inp.length(); i++)
    {
        if (inp[i] == '(')
        {
            stray_bckt++;
            bckt_count++;
        }
        if (inp[i] == ')')
        {
            stray_bckt--;
            bckt_count++;
        }
    }

    bckt_count = bckt_count / 2;

    if (stray_bckt != 0)
    {
        cout << "Bracket Error" << endl;
        return false;
    }
    else
    {
        return true;
    }
}

int Bckt_Sept(string inp)
{
    for (int i = 0; i < inp.length(); i++)
    {
        if (inp[i] == ')')
        {
            bckt[1] = i;
            for (int j = i; j >= 0; j--)
            {
                if (inp[j] == '(')
                {
                    bckt[0] = j;
                    return 0;
                }
            }
        }
    }
    return 1;
}

double MultiCalculate(string inp)
{
    double r;
    SeparateNumsnOps(inp);
    for (int l = 0; l < 2; l++)
    {
        for (int i = 0; i < op_count; i++)
        {
            if (ops[i].type == '/')
            {
                int n;
                r = Calculate(nums[i], ops[i].type, nums[i+1]);
                nums[i] = r;
                for (int n = 0; n < op_count - i - 1; n++)
                {
                    ops[i+n].type = ops[i+n+1].type;
                }
                ops[op_count-1].type = '0';
                for (n = 1; n < num_count - i; n++)
                {
                    nums[i + n] = nums[i + n + 1];
                }
                nums[i + n] = 0;
                i = i - 1;
            }
        }
        for (int i = 0; i < op_count; i++)
        {
            if (ops[i].type == '*')
            {
                int n;
                r = Calculate(nums[i], ops[i].type, nums[i+1]);
                nums[i] = r;
                for (int n = 0; n < op_count - i - 1; n++)
                {
                    ops[i+n].type = ops[i+n+1].type;
                }
                ops[op_count-1].type = '0';
                for (n = 1; n < num_count - i; n++)
                {
                    nums[i + n] = nums[i + n + 1];
                }
                nums[i + n] = 0;
                i = i - 1;
            }
        }
        for (int i = 0; i < op_count; i++)
        {
            if (ops[i].type == '+')
            {
                int n;
                r = Calculate(nums[i], ops[i].type, nums[i+1]);
                nums[i] = r;
                for (int n = 0; n < op_count - i - 1; n++)
                {
                    ops[i+n].type = ops[i+n+1].type;
                }
                ops[op_count-1].type = '0';
                for (n = 1; n < num_count - i; n++)
                {
                    nums[i + n] = nums[i + n + 1];
                }
                nums[i + n] = 0;
                i = i - 1;
            }
        }
        for (int i = 0; i < op_count; i++)
        {
            if (ops[i].type == '-')
            {
                int n;
                r = Calculate(nums[i], ops[i].type, nums[i+1]);
                nums[i] = r;
                for (int n = 0; n < op_count - i - 1; n++)
                {
                    ops[i+n].type = ops[i+n+1].type;
                }
                ops[op_count-1].type = '0';
                for (n = 1; n < num_count - i; n++)
                {
                    nums[i + n] = nums[i + n + 1];
                }
                nums[i + n] = 0;
                i = i - 1;
            }
        }
    }
    r = nums[0];
    num_count = 0;
    op_count = 0;
    return r;
    return 0;
}

double Calculate(double l, char op, double r)
{
    switch (op)
    {
    case '/':
        return l / r;
        break;
    case '*':
        return l * r;
        break;
    case '+':
        return l + r;
        break;
    case '-':
        return l + r;
        break;
    }
    return 0;
}

void SeparateNumsnOps(string inp)
{
    string temp;
    for (int i = 0; i < inp.length(); i++)
    {
        if ((inp[i] == '+' || inp[i] == '-' || inp[i] == '*' || inp[i] == '/') && isdigit(inp[i - 1]) != 0)
        {
            ops[op_count].type = inp[i];
            ops[op_count].pos = i;
            op_count++;
        }
        if (isdigit(inp[i]) != 0)
        {
            if (inp[i - 1] == '+' || inp[i - 1] == '-') //If Num is preceded by + or - take the value with + or - included
            {
                int j = i - 1;
                do
                {
                    if (isdigit(inp[j]) != 0)
                    {
                        temp = temp + to_string(inp[j] - '0');
                        j++;
                    }
                    else //For . character
                    {
                        temp = temp + inp[j];
                        j++;
                    }
                } while (isdigit(inp[j]) != 0 || inp[j] == '.');

                nums[num_count] = stod(temp);
                temp = "";
                i = j - 1;
                num_count++;
            }
            else
            {
                int j = i;
                do
                {
                    if (isdigit(inp[j]) != 0)
                    {
                        temp = temp + to_string(inp[j] - '0');
                        j++;
                    }
                    else //For . character
                    {
                        temp = temp + inp[j];
                        j++;
                    }
                } while (isdigit(inp[j]) != 0 || inp[j] == '.');

                nums[num_count] = stod(temp);
                temp.erase();
                i = j - 1;
                num_count++;
            }
        }
    }
}
