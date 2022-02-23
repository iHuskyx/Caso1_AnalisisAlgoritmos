// Caso #1 - Análisis de algoritmos Grupo 1 - Andrea Li 2021028783
#include <bits/stdc++.h>
#include <string>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


/* compareTriplets2 es mejor que compareTriplets1 porque en la primera implementación se utiliza un ciclo for,
 * en el cual se realizan 4 comparaciones del for (cuando verifica si se ha llegado a la condición de parada)
 * y 6 internas (comparar los elementos de a y b). Mientras que en la segunda se utilizan un total de 6 comparaciones.
*/
vector<int> compareTriplets1(vector<int> a, vector<int> b) {
    int a_score = 0;
    int b_score = 0;

    for (int i = 0; i < 3; i++) {
        if (a[i] > b[i])
            a_score++;
        else if (a[i] < b[i])
            b_score++;
    }

    vector<int> result{a_score, b_score};
    return result;
}

vector<int> compareTriplets2(vector<int> a, vector<int> b) {
    int a_score = 0;
    int b_score = 0;

    if (a[0] > b[0])
        a_score++;
    else if (a[0] < b[0])
        b_score++;

    if (a[1] > b[1])
        a_score++;
    else if (a[1] < b[1])
        b_score++;

    if (a[2] > b[2])
        a_score++;
    else if (a[2] < b[2])
        b_score++;

    vector<int> result{a_score, b_score};
    return result;
}

/* timeConversion2 es mejor que timeConversion1 debido a que utilizamos operaciones aritméticas y solamente
 * 2 ifs, mientras que en timeConversion1 utilizamos un total de 6 expresiones condicionales.
 */
string timeConversion1(string s) {
    string result;
    string time = s.substr(8,1);    // "A" o "P"
    int hours = stoi(s.substr(0,2)); //Tomar el substring con las horas y pasarlo a int

    if (time == "A") {  //Si es AM
        if (hours == 12)
            result = "00";
        else
            result = s.substr(0,2);
    }else { // Si es PM
        if (hours < 12) {
            hours = 12 + hours;
            result = to_string(hours);
        }else
            result = "12";
    }
    result = result + s.substr(2,6);  // Concatenarle a las horas -> mm:ss
    return result;
}

string timeConversion2(string s) {
    string time = s.substr(8,1); //"A" o "P"
    string full_time = s.substr(2, 6); // :mm:ss
	int hrs = stoi(s.substr(0,2)); //Tomar el substring con las horas y pasarlo a int
	int factor = ((hrs%12)/hrs); //Para PM: =0 si hrs=12 | =1 en otro caso

	if (time == "A")
        factor--; //Para AM: =-1 si hrs=12 | =0 en otro caso

    hrs += (12 * factor);

    //Actualizar la hora completa
    // Si la hora es menor que 10, se concatena el "0" antes que el número
	full_time = (hrs<10) ? "0"+to_string(hrs)+full_time : to_string(hrs)+full_time;

	return full_time;
}

/*
 * Ejercicios que solo se hace la implementación más optimizada
 */

/*
 * Cipher: Debe decodificar el mensaje enviado.
 * Recibe 3 parámetros: Las "k" veces que se repitió el mensaje, "n" es el largo del string resultado
 * y "s" es el string con el mensaje codificado
 * Retorna un string
 */
string cipher(int k, int n, string s) {
    vector<char> result(n);

    result[0] = s[0]-48;

    // Calcular los elementos de 1 a k-1
    for (int i = 1; i < k; i++) {
        result[i] = s[i-1] ^ s[i];
    }

    // Calcular los elementos de k en adelante
    char aux;
    for (int i = k; i < n; i++) {
        aux = '0';
        for (int j = i-(k-1); j < i; j++) {
            aux = aux ^ result[j];
        }
        result[i] = aux ^ s[i];
    }

    // Armar el string con el resultado
    string final_result = "";
    for (int i = 0; i < n; i++) {
        final_result += result[i]+48;
    }
    return final_result;
}

int main(){
    // ---------------- Prueba 1 para compareTriplets ----------------
    cout << "Prueba #1 para compareTriplets" << endl;
    vector<int> a = {5,3,1};
    vector<int> b = {5,2,6};
    cout << "a = {5,3,1}" << endl;
    cout << "b = {5,2,6}" << endl;
    vector<int> result1_triplets = compareTriplets2(a, b);
    cout << "Resultado = ";
    cout << "a = " << result1_triplets[0] << " | b = " << result1_triplets[1] << endl;

    // ---------------- Prueba 2 para compareTriplets ----------------
    cout << endl;
    cout << "Prueba #2 para compareTriplets" << endl;
    vector<int> a2 = {2,5,8};
    vector<int> b2 = {1,7,9};
    cout << "a = {2,5,8}" << endl;
    cout << "b = {1,7,9}" << endl;
    vector<int> result2_triplets = compareTriplets2(a2, b2);
    cout << "Resultado = ";
    cout << "a = " << result2_triplets[0] << " | b = " << result2_triplets[1] << endl;

    // ---------------- Prueba 1 para TimeConversion ----------------
    cout << endl;
    cout << "Prueba #1 para TimeConversion" << endl;
    string s = "12:00:10AM";
    cout << s << endl;
    string result1_conversion = timeConversion1(s);
    cout << "Resultado = ";
    cout << result1_conversion << "\n";

    // ---------------- Prueba 2 para TimeConversion ----------------
    cout << endl;
    cout << "Prueba #2 para TimeConversion" << endl;
    s = "02:30:05PM";
    cout << s << endl;
    string result2_conversion = timeConversion2(s);
    cout << "Resultado = ";
    cout << result2_conversion << "\n";

    // ---------------- Prueba 1 para Cipher ----------------
    cout << endl;
    cout << "--------------------------------" << endl;
    cout << "Prueba #1 para Cipher" << endl;
    cout << "k = 3, n = 7, s = 1110100110" << endl;
    string result = cipher(4, 7, "1110100110");
    cout << "Resultado = " << result << "\n";

    // ---------------- Prueba 2 para Cipher ----------------
    cout << endl;
    cout << "Prueba #2 para Cipher" << endl;
    cout << "k = 2, n = 6, s = 1110001" << endl;
    result = cipher(2, 6, "1110001");
    cout << "Resultado = " << result << "\n";

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}


