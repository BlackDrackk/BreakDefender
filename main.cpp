/*
Directives de préprocesseurs, le préprocesseur est un programme qui va parser les fichiers (parcourir les fichiers) et à chaque instruction/directives il va executer l'ordre qu'on lui donne ici "include ..."" 
*/

#include <iostream>

/*
Fonction principale "main"
Tous les programmes commencent par la fonction main
*/


int main()
{
    int age = 0;
    std::cout << "How old are you ?";
    std::cin >> age;
    std::cout << "I am : " << age;

    return 0;
}



