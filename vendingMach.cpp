
#include<iostream>
#include<math.h>

using namespace std;

int nic=25, dim=25, qua=25, one=0, fiv=0; // keeps count of vending machine coins
int price;

void stockStatus(void); //prints the current status of coins in vending machine
int inputPrice(void); //takes price input and checks for error or quit
void printMenu(void); // prints the money input menu
char chooseMenu(void); // takes user input and checks for error
bool paymentDue(int ); //calculates due payment and takes input
void giveChange(int ); //gives change according to greedy algorithm
void total(void); //calculates totals of the vending machine

int main(){
cout<<"Welcome to the vending machine change maker program"<<endl;
cout<<"Change maker initialized."<<endl;

stockStatus();

while(true){ //infinite loop until user quits
price = inputPrice(); //returns -1 if user presses 'q'
if(price == -1) break; //breaks the loop in case user presses 'q'
printMenu();
if(!paymentDue(price)) //if user cancels the payment mid way, returns change
giveChange(price);
}

total(); //prints total

return 0;
}

void stockStatus(){
cout<<" Stock contains:"<<endl;
cout<<nic<<" nickels"<<endl;
cout<<dim<<" dimes"<<endl;
cout<<qua<<" quarters"<<endl;
cout<<one<<" ones"<<endl;
cout<<fiv<<" fives"<<endl;
cout<<" "<<endl;
}

int inputPrice(){
cout<<"Enter the purchase price (xx.xx) or 'q' to quit: ";
float f;
cin >> f;
if(cin.fail()) return -1; //returns -1 if 'q' is entered
int x = (int) (f*100.0 + 0.5); //converts decimal to integer and stores value in cents
if(x % 5 == 0) return x; //checks value divisible by 5
cout << "Illegal price: Must be a non-negative multiple of 5 cents." << endl;
return inputPrice(); //recurses if error
}

void printMenu(){
cout << "Menu for deposits:" << endl;
cout << "'n' - deposit a nickel" << endl;
cout << "'d' - deposit a dime" << endl;
cout << "'q' - deposit a quarter" << endl;
cout << "'o' - deposit a one dollar bill" << endl;
cout << "'f' - deposit a five dollar bill" << endl;
cout << "'c' - cancel the purchase" << endl;
}

char chooseMenu(){
char ch;
cin >> ch; //takes input
if (ch == 'n' || ch == 'd' || ch == 'q' || ch == 'o' || ch == 'f' || ch == 'c') //checks input value
return ch;

cout << "Illegal selection" << endl;
return chooseMenu(); //recurses if wrong input
}

bool paymentDue(int price){
if(price <= 0){ //moves to change menu if no payment is due
cout<<" Please take the change below." << endl;
giveChange(-price); //calls change method
return true; //payment not cancelled
}
cout << "Payment due: " << price/100 << " dollars and " << price%100 << " cents" << endl;

char ch = chooseMenu();
switch(ch){
case 'n':
nic++;
price -= 5;
break;
case 'd':
dim++;
price -= 10;
break;
case 'q':
qua++;
price -= 25;
break;
case 'o':
one++;
price -= 100;
break;
case 'f':
fiv++;
price -= 500;
break;
case 'c':
::price -= price; //updates the global price value, to return the amount already deposited by the user
return false;
}

return paymentDue(price);
}

void giveChange(int price){
if(price == 0){
cout<<"No change due."<<endl;
}

int x;

//order of if statements executes the greedy approach

if(price/500 > 0 && fiv > 0){
x = min(price/500, fiv);
fiv -= x;
price -= 500*x;
cout<<x<<" fives"<<endl;
}
if(price/100 > 0 && one > 0){
x = min(price/100, one);
one -= x;
price -= 100*x;
cout<<x<<" ones"<<endl;
}
if(price/25 > 0 && qua > 0){
x = min(price/25, qua);
qua -= x;
price -= 25*x;
cout<<x<<" quarters"<<endl;
}
if(price/10 > 0 && dim > 0){
x = min(price/10, dim);
dim -= x;
price -= 10*x;
cout<<x<<" dimes"<<endl;
}
if(price/5 > 0 && nic > 0){
x = min(price/5, nic);
nic -= x;
price -= 5*x;
cout<<x<<" nickels"<<endl;
}
if(price > 0){
cout<<"Machine is out of change."<<endl;
cout<<"See store manager for remaining refund."<<endl;
cout<<"Amount due is: "<<price/100<<" dollars and "<<price%100<<" cents"<<endl;
}

stockStatus();
}

void total(){
int tot = nic*5 + dim*10 + qua*25 + one*100 + fiv*500;
cout << "Total: " << tot/100 << " dollars and " << tot%100 << " cents"<<endl;
}
