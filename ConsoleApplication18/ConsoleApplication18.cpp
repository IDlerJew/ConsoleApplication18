// ConsoleApplication18.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Структура данных для хранения ребра Graph
struct Edge {
    int src;
    int dest;
};

// Класс для представления graphического объекта
class Graph
{
public:
    // вектор векторов для представления списка смежности
    vector<Edge> edges;
    int maxTimeJob;
    int maxTimeAddJob;
     int n ;

    // Конструктор Graphа
    Graph(vector<Edge> const& _edges, int _n,  int _maxTimeJob,  int _maxTimeAddJob)
    {
 
        // добавляем ребра в ориентированный graph
        for (int i=0;i<_n;i++)
        {
            // вставляем в конце
            edges.push_back(_edges[i]);

            // раскомментируйте следующий код для неориентированного Graph
            // adjList[edge.dest].push_back(edge.src);
        }
        n = _n;
        maxTimeJob= _maxTimeJob;
        maxTimeAddJob= _maxTimeAddJob;
    }
    string checkJobTime() {              // проверяем поминутно всегда ли есть 2 сторожа
        string intervals;
        bool CheckIntevals=true ;
        for (int i = 0; i <= maxTimeJob; i++) {
            int testDoubleWork=0;
            bool check = false;
            
            for (int j = 0; j < n; j++) {
                if (edges[j].src <= i&& i <=edges[j].dest) {
                    testDoubleWork++;
                }
                if (testDoubleWork >= 2) {
                    check = true;
                    break;
                }
            }

            if (check) {

            }
            else {
                CheckIntevals = true;
                intervals += std::to_string(i);
                i++;
                for (; i <= maxTimeJob; i++) {
                    testDoubleWork = 0;
                    for (int j = 0; j < n; j++) {
                        if (edges[j].src <= i && i <= edges[j].dest) {
                            testDoubleWork++;
                        }
                        if (testDoubleWork < 2) {
                            
                            continue;
                        }
                        else {
                            CheckIntevals = false;
                            break;
                           
                        }
                       
                    }
                    if (i == maxTimeJob) {
                        intervals += "-";
                        intervals += std::to_string(i);
                        intervals += ";";
                    }
                    if (!CheckIntevals) {
                        intervals += "-";
                        intervals += std::to_string(--i);
                        intervals += ";";
                        break;
                    }
                }
                
               
            }



        }
        
        return intervals;
   }
    bool checkSwap() {
        int sum=0;
        for (int i = 0; i < n; i++) { // просто по сумме проверяем можно ли переставить и всё пойдет  
            sum += edges[i].dest - edges[i].src;
        }
        if (sum >= maxTimeJob * 2) return true;
        else return false;
    }
    bool TrytoSwap() {
        if (checkSwap()) {
            cout << "Поменять можно вот новый список " << endl;

            vector<Edge> edges3;

            for (int i = 0; i < n; i++)
            {

                edges3.push_back(edges[i]); //копирование нашего графа чтобы потом можно было все проверить 
            }
            int sum = 0;
            int* arraySize = new int[n];
            bool testMaxtimeJob = false;
            for (int i = 0; i < n; i++)
            {
                int sum = 0;
                for (int i = 0; i < n; i++) {//чистка перед новой итерацией 
                    arraySize[i] = -1;
                }



                sum += edges[i].dest - edges[i].src;
                arraySize[i] = i;
                if (sum == maxTimeJob)break;// проверка на случай если один интервал покрывает всё время работы 

                for (int j = i + 1; j < n; j++) {
                    sum += edges[j].dest - edges[j].src;
                    arraySize[j] = j;
                    if (sum == maxTimeJob) {
                        testMaxtimeJob = true;
                        break;
                    }
                    if (sum > maxTimeJob)break;
                }
                if (testMaxtimeJob) break;
            }
            int lastTime = 0;
            for (int i = 0; i < n; i++) {
                if (arraySize[i] != -1) {
                    int intervals = edges3[i].dest - edges3[i].src;
                    edges3[i].src = lastTime;
                    edges3[i].dest = lastTime + intervals;
                    lastTime = edges3[i].dest;
                }
            }
            lastTime = 0;
            for (int i = 0; i < n; i++) {
                if (arraySize[i] == -1) {
                    int intervals = edges3[i].dest - edges3[i].src;
                    edges3[i].src = lastTime;
                    edges3[i].dest = lastTime + intervals;
                    lastTime = edges3[i].dest;
                }
            }
            Graph grap2(edges3, n,maxTimeJob,maxTimeAddJob);
            printGraph(grap2);
            return true;

        }
        else {
            
            cout << " Поменять нельзя ";
            return false;
        }
    }
    void printGraph(Graph const& graph)
    {
        for (int i = 0; i < n; i++)
        {
            cout << graph.edges[i].src << " ——> " << graph.edges[i].dest;

            cout << endl;
        }
    }
    void addEmployee(string intervals) {
        string number1;
        string number2;
        for (int i = 0; i < intervals.size(); i++) {
            number1.clear();
            number2.clear();
            for (; intervals[i]!='-'; i++) {
                number1 += intervals[i];
            }
            i++;
            for (; intervals[i] != ';'; i++) {
                number2 += intervals[i];
            }
            
            int inter1 = stoi(number1);
            
            int inter2 = stoi(number2);
            
            while (inter1 < inter2) {
                Edge edge = { inter1,inter1 + maxTimeAddJob };
                edges.push_back(edge);
                n++;
                inter1 += maxTimeAddJob;
            }
        }
    }
};






int main()
{
    setlocale(0, "rus");
    //Пример где всё правильно 
    // vector<Edge> edges = { {0, 20}, {20, 40}, {0, 40}, {40, 80}, {80, 100}, {40, 60}, {60, 100}}; int n = 7; int maxTimeJob = 100; int maxTimeAddJob=5;
    //Пример где надо просто gjvtyznm vtcnfvb 
   // vector<Edge> edges = { {0, 50}, {0, 50}, {20, 60}, {20, 60}, {60, 200}, {60, 120}, {0, 80} }; int n = 7; int maxTimeJob = 200; int maxTimeAddJob = 5;
    // Пример где поменять нельзя надо добавлять 
    vector<Edge> edges = { {0, 5}, {5, 10}, {25, 40}, {10, 25}, {0, 15} }; int n = 5; int maxTimeJob = 50; int maxTimeAddJob = 5;
    
    Graph graph(edges, n, maxTimeJob, maxTimeAddJob);
    graph.printGraph(graph);
    string abc= graph.checkJobTime();
    if (abc.empty()) {
      cout <<"Менять ничего не надо везде минимум по 2 сторожа  " <<endl;
    }
    else {
        cout << "список интервалов когда не хватает сторожей " << abc<< endl;
        if (!graph.TrytoSwap())
        {  
            cout << "Добавляем новых сторожей "<<endl;
            graph.addEmployee(abc);
            graph.printGraph(graph);
        }

    }
    
    
    
    //cout << graph.checkSwap();
    //graph.TrytoSwap();

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
