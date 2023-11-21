//
//  main.cpp
//  fib
//
//  Created by Prashant Gurung on 16/05/2022.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>

#define subStringLen 10 // for the purpose of calculating 10 digit onlys

int count = 1;
long const N = 9999999999;

char alp[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

std::vector<bool> is_prime(N+1,true);
std::map<long,long> primeList;   // to store this data  (index,prime number of the fibonacci sequence string)


 void sieve() { //effective way to calculate prime numbers once and store in a vector

    is_prime[0] = is_prime[1] =  false;

      for (unsigned long long i = 0; i <= N; i++) {
        
        if (is_prime[i] && i * i <= N)
        {
           
            for (unsigned long long j = i * i; j <= N; j += i)
                is_prime[j] = false;
        
        }
    }

}

int countDigit(unsigned long n)
{
   if(n == 0)
     return 1;
    int count = 0;
    while (n != 0)
    {
        n = n / 10;
        ++count;
    }
    return count;
}

unsigned long fib(int n) // calculate the fibonacci number
{
     
    unsigned long f[n + 2];
    int i;
 
    f[0] = 0;
    f[1] = 1;
 
    for(i = 2; i <= n; i++)
    {
         
       f[i] = f[i - 1] + f[i - 2];
    }
    return f[n];
}



std::string FibNumberSequence(unsigned long x)
{
    std::string fibNum = "";
    for(int i = 1; (i<=x+1) ;i++)
    {
        fibNum = fibNum + std::to_string(fib(i));
    }
    return fibNum;
}

void checkIfPrimeAndStore(std::string sub)
{
    std::stringstream x;
    x << sub;
    long n = std::stol(x.str()); //converting string to long
    if(countDigit(n)==10) //make sure it is 10 digit when there might be a zero in the 10th place of the number for example 0012486542 which should be handled by std::stol but just in case
       {
        if(is_prime.at(n)) // check if n is a prime number by looking up in the vector is_prime where the indexes represent the number and its value , true or false    denotes if its prime or not
          {
            primeList.insert(std::pair<long,long>(count,n));
            count = count + 1;
          }
           x.str("");
           
       }
}

void PrimeSeqNum(unsigned long len,std::string &tempStr)
{
    std::string subStr = "";
    
    for(int i=0;(i<=len-subStringLen);i++)
    {
        subStr = tempStr.substr(i,subStringLen);
        
       // std::cout<< i+1 << " : " << "Current substring is " << subStr << std::endl;
        
        checkIfPrimeAndStore(subStr); // check if the substring is a prime and if yes store it on the map;
    }
}

std::string numToLetter(long num) // converting 2 digit number to the corresponding Letter
{
    std::string temp1 = std::to_string(num);
    std::string temp2 = "";
    std::string temp3 = "";
    std::string temp4 = "";
    
    long alphabet = 0;
    int mod = 0;
    
    for(int i = 0; i<10-1; i=i+2)
    {
        std::string temp2 = temp1.substr(i,2);
        alphabet = std::stol(temp2);
        mod = alphabet % 26;
       // std::cout << temp2 << " : num = " << alphabet << " : mod = " << mod << " : CHARACTER " << alp[mod] << std::endl;
       // std::cout << alp[mod] ;
        temp3 = alp[mod];
    //    std::cout << "tmp3 : "<< temp3 << std::endl;
        temp4 = temp4 + temp3;
      
    }
   // temp4 = "";
 //   std::cout << "tmp4 : "<< temp4 << std::endl;
    return temp4;
}


void createFileofFibonacciSequence(){

    std::map<long,long>::iterator it;
    std::fstream primeNumbers;
    primeNumbers.open("primeNumbers.txt", std::fstream::out);
    if(!primeNumbers)
    {
        std::cout << " File not created! ";
    }
    else{
        std::cout << "File Created Successfully" << std::endl;
        for(it = primeList.begin(); it!=primeList.end();it++)
        {
            primeNumbers << it->first << "," << numToLetter(it->second) << "\n" ;
        }
        primeNumbers.close();
    }

}

int main() {
       
    sieve(); // insert prime numbers in the vector so that the method CheckifPrimeandStore called by PrimeSeqNum will use it to look up if the passed number is prime
    
  //*** THIS FOLLOWING SEQUENCE OF CODE WILL GENERATE THE FIBONACCI SEQUENCE NUMBERS AND STORE IT IN A STRING, THEN EVALUATE EACH STRING OF LENGTH 10 FROM THE START IF ITS A PRIME NUMBER AND THEN STORE IN THE MAP, primeList. THEN IT STORES IT IN THE FILE primeNumbers.txt SO THAT NEXT TIME, WE CAN USE THE FILE TO LOOK UP THE PRIME NUMBERS GENERATED FROM THE FIBONACCI SEQUENCE INSTEAD OF THE TIME CONSUMING FUNCTIONS ALREADY PERFORMED. SO, IF THE FILE IS ALREADY CREATED THEN COMMENT OUT THIS BLOCK OF CODES AND USE THE LINES OF CODE BELOW THIS.  ***
    
    std::string result = FibNumberSequence(72000); // make the string out of the fibonacci sequence upto fib(72000)
    unsigned long lengthStr = result.length(); // length of the string
    PrimeSeqNum(lengthStr,result); // evaluate and store all the prime numbers in the map
    createFileofFibonacciSequence(); //store it in a file called PrimeNumbers.txt which is created in this directory :  /Users/prashantgurung/Library/Developer/Xcode/DerivedData/fib-axrhiqmgwbyflfgxwqxidorszkwe/Build/Products/Debug

    

    
    //*** UNBLOCK THIS SECTION OF CODE TO READ FROM THE FILE OF PRIME NUMBERS AND DO TESTING OR OTHER TASKS ***
  /*
    std::ifstream listPrimeNum("primeNumbers.txt"); // open this file
    if(!listPrimeNum.is_open()){
        std::cout<<"Failed to open File" << std::endl;
        return 0;
    }
    std::string tempString,numIndex;
    std::string thePrimeNumber;
    long n,p;
    while(getline(listPrimeNum,tempString)){
        std::stringstream ss(tempString);
        getline(ss, numIndex, ',');
        getline(ss,thePrimeNumber);
            std::cout << numIndex << std::endl;
            std::cout << thePrimeNumber << std::endl;
        n = std::stol(numIndex);
        p = std::stol(thePrimeNumber);
        primeList.insert(std::pair<long,long>(n,p)); // populate the map primeList
    }
    
    */
    
    //TESTING
    
    numToLetter(2584418167); // this is the first prime number in the sequence, and evaluates to ZGPDP
    numToLetter(7682176069); // the prime number at 44722 is 7682176069 and output its associated word
    numToLetter(1836984151); // the prime number at 53215 is 1836984151 and output its associated word

 
    
    return 0;
}
