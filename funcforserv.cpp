#include "funcforserv.h"

const int maxn = 4; // максимальное количество вершин в графе

QVector<int> graph[maxn]; // список смежности графа
bool adjacencyMatrix[maxn][maxn]; // матрица смежности графа
QString matrix1;

QByteArray parse(QString str){
    QStringList params = str.split("|");   //формат msg: function|params0|params1... auth email password
    qDebug()<<params[0];
    if (params[0] =="auth"){
        QString mail=params[1];           //разделяем данные для функций
        QString pass= params[2];
        return auth(mail,pass);
    }
    else if (params[0] =="rege"){
        QString mail=params[1];           //разделяем данные для функций
        QString pass= params[2];
        QString verpass=params[3];
            return rege(mail,pass,verpass);

   }
   else if (params[0] == "stat"){
     QString mail=params[1];
      stat(mail);

   }
   else if (params[0] == "task1"){

            QString mail=params[1];
          return task1(mail);
       }
   else if (params[0] == "task2"){

       QString mail=params[1];
        return task2(mail);

   }
   else if (params[0] == "task3"){
            return get_task3();

    }
   else if (params[0] == "task4"){
        QString mail=params[1];
            return task4(mail);
   }
    else if (params[0] == "checktask1"){

        QString mail=params[1];
        QString variant=params[2];
        QString answer=params[3];

           return checktask1(mail,variant,answer);
        }
    else if (params[0] == "checktask2"){

        QString mail=params[1];
        QString variant=params[2];
        QString answer=params[3];

           return checktask2(mail,variant,answer);
        }
    else if (params[0] == "checktask3"){

        QString mail=params[1];
        QString variant=params[2];
        QString answer=params[3];

           return checktask3(mail,variant,answer);
        }
    else if (params[0] == "checktask4"){

            QString mail=params[1];
            QString variant=params[2];
            QString answer=params[3];

               return checktask4(mail,variant,answer);
            }
   else{
             return "Invalid function name";
   }
   return "parse";
}

QByteArray rege(const QString& email,const QString& password,const QString& verifypass){

    QString query = QString("INSERT INTO users (mail, pass) VALUES(\"%1\",\"%2\")").arg(email, password);
    //Database::getInstance()->execQuery(query).size()>0
    Database::getInstance()->execQuery(query);  
    QString s = Database::getInstance()->execQuery("SELECT * from users where mail = \"" + email+"\"");
    if (s.size()>0) {
        return "rege+";
    } else {
        return "rege-";
    }
}

QByteArray auth(const QString& email,const QString& password){
    QString query = QString("SELECT * FROM users WHERE mail = \"" + email+"\"");
    qDebug()<<query;
    if (Database::getInstance()->execQuery(query).size()>0){  // Если найдено больше нуля записей с заданным именем пользователя,
        return "auth+";
        Database::getInstance()->execQuery("UPDATE users SET in_sys = 1 WHERE mail = \"" + email+"\"");
    }
    else                                                                     // Иначе пользователь с заданным именем не найден в базе данных.
        return "auth- ";
}

QString stat(const QString& email){
   QString query = ("SELECT task1, task2, task3, task4 FROM users WHERE mail = \"" + email+"\"");
   qDebug()<<query;
   QString response = "";
    if (Database::getInstance()->execQuery(query).size()>0){  
        response = Database::getInstance()->execQuery(query);
        return response;
    }
    else                                                               
        return "stat-";
}

QByteArray task1(const QString& email){
    QString answer;
    // Задаем случайное количество вершин и ребер
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> vertexDis(4, 7); // от 2 до 10 вершин
    std::uniform_int_distribution<> edgeDis(4, (vertexDis(gen) * (vertexDis(gen) - 1)) / 2); // от 1 до n*(n-1)/2 ребер
    int n = vertexDis(gen); // количество вершин
    int m = edgeDis(gen); // количество ребер
    answer.append(QString::number(n)+"/");
    answer.append(QString::number(m)+"/");

    // генерируем случайный список ребер графа
    QVector<std::pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v) {
            edges.push_back(std::make_pair(u, v));
        }
    }

    // выводим список вершин и ребер на экран
    //answer.append( "Vertices list: " + '\n');
    //for (int i = 0; i < n; i++) {
    //    answer.append( QString::number(i) + " ");
    //}
    //answer.append("\n");

    //answer.append( "Edges list: " + '\n');
    int k = 0;
    for (auto i:edges) {
        if(k==m){
            break;
        }
        answer.append(QString::number(i.first) + "-" + QString::number(i.second) + ";");
        k+=1;
    }

    // строим матрицу смежности графа
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        for (int j : graph[i]) {
            adjacencyMatrix[i][j] = 1;
        }
    }

    //answer.append("||");
    //выводим матрицу смежности на экран
    //cout << "Adjacency matrix: " << endl;
    //for (int i = 0; i < n; i++) {
    //    for (int j = 0; j < n; j++) {
    //        qDebug()<<(QString::number(adjacencyMatrix[i][j]) + " ");
    //    }
    //}
    QString matrix;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix.append(QString::number(adjacencyMatrix[i][j]) + " ");
        }

    }
    qDebug() << matrix;


    return answer.toUtf8();
};

QByteArray task2(const QString& email){



    QString answer;
    // Задаем случайное количество вершин и ребер
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> vertexDis(4, 7); // от 2 до 10 вершин
    std::uniform_int_distribution<> edgeDis(4, (vertexDis(gen) * (vertexDis(gen) - 1)) / 2); // от 1 до n*(n-1)/2 ребер
    int n = vertexDis(gen); // количество вершин
    int m = edgeDis(gen); // количество ребер
    answer.append(QString::number(n)+"/");
    answer.append(QString::number(m)+"/");

    // Создаем матрицу смежности и заполняем ее случайными значениями
    QVector<QVector<int>> adjacencyMatrix(n, QVector<int>(n, 0));
    std::uniform_int_distribution<> dis(0, 1);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int value = dis(gen);
            adjacencyMatrix[i][j] = value;
            adjacencyMatrix[j][i] = value;
        }
    }

    // Создаем список вершин
    QVector<int> vertices(n);
    for (int i = 0; i < n; i++) {
        vertices[i] = i + 1;

    }

    // Создаем список ребер

    QVector<std::pair<int, int>> edges;{

        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < n; j++)
            {


                edges.push_back(std::make_pair(i, j));


            }
        }
    }
    // Создаем матрицу инцидентности и заполняем ее нулями
    QVector<QVector<int>> incidenceMatrix(n, QVector<int>(m, 0));

    // Заполняем матрицу инцидентности
    for (int i = 0; i < m; i++) {
        int startVertex = edges[i].first;
        int endVertex = edges[i].second;
        int startVertexIndex = startVertex ;
        int endVertexIndex = endVertex ;
        incidenceMatrix[startVertexIndex][i] = 1;
        incidenceMatrix[endVertexIndex][i] = -1;
    }

    // Выводим матрицу инцидентности в консоль
    QString matrix;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //qDebug() << (QString::number(incidenceMatrix[i][j]) + " ");
        }

    }

    qDebug() << edges;
    // выводим список вершин и ребер на экран




    //answer.append( "Edges list: " + '\n');
    int k = 0;
    for (auto i:edges) {
        if(k==m){
            break;
        }
        answer.append(QString::number(i.first) + "-" + QString::number(i.second) + ";");
        k+=1;
    }
    qDebug() << answer;
    /* // Создаем матрицу инцидентности и заполняем ее нулями
    QVector<QVector<int>> incidenceMatrix(n, QVector<int>(m, 0));

    // Заполняем матрицу инцидентности
    for (int i = 0; i < m; i++) {
        int startVertex = edges[i].first;
        int endVertex = edges[i].second;
        int startVertexIndex = startVertex - 1;
        int endVertexIndex = endVertex - 1;
        incidenceMatrix[startVertexIndex][i] = 1;
        incidenceMatrix[endVertexIndex][i] = -1;
    }
    answer.append("");
    // Выводим матрицу инцидентности в консоль
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            qDebug() << (QString::number(incidenceMatrix[i][j]) + " ");
        }

    }
    */

    return answer.toUtf8();

}

QByteArray checktask3(const QString& email, const QString& variant, const QString& answer){

    //СЧИТЫВАНИЕ ГРАФА ПОЛЬЗОВАТЕЛЯ: НАЧАЛО

    std::string client_graph = variant.toStdString();
    int count, j = 0;
    std::vector<int> sv;
    std::set<int> verticles;
    for (size_t i = 0; i < client_graph.length(); i++){
        if (isdigit(client_graph[i])){
            j = i;
            while (isdigit(client_graph[i])){
                i++;
            }
            std::istringstream edge(client_graph.substr(j, i));
            edge >> count;
            sv.push_back(count);
            verticles.insert(count);
        }
    }

    /*std::cout << "Vector =  ";
    for (int i = 0; i < sv.size(); i++) std::cout << sv[i] << " ";
    std::cout << std::endl;*/
    std::vector<std::vector<int>> v;
    int max = *max_element(sv.begin(), sv.end());

    v.resize(max+1);

    for (int i=0;i<=sv.size()-1;i+=2)
    {
        v[sv[i]].push_back(sv[i + 1]);
        v[sv[i + 1]].push_back(sv[i]);
    }
    /*//вывод смежностей
    for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v[i].size(); j++)
            std::cout<<v[i][j] << " ";
    }
    std::cout<<std::endl;*/

    //СЧИТЫВАНИЕ ГРАФА ПОЛЬЗОВАТЕЛЯ: КОНЕЦ

    //СЧИТЫВАНИЕ СГЕНЕРИРОВАННОГО ГРАФА: НАЧАЛО

    std::string gen_graph = answer.toLocal8Bit ().constData ();
    std::vector<int> sv2;
    std::set<int> rand_vert;
    std::vector<std::vector<int>> v2;
    int count2, j2 = 0;
    for (size_t i = 0; i < gen_graph.length(); i++){
        if (isdigit(gen_graph[i])){
            j2 = i;
            while (isdigit(gen_graph[i])){
                i++;
            }
            std::istringstream edge(gen_graph.substr(j2, i));
            edge >> count2;
            sv2.push_back(count2);
            rand_vert.insert(count2);
        }
    }

    /*std::cout << "Vector =  ";
    for (int i = 0; i < sv2.size(); i++) std::cout << sv2[i] << " ";
    std::cout << std::endl;*/
    int max2 = *max_element(sv2.begin(), sv2.end());
    v2.resize(max2+1);

    for (int i=0;i<=sv2.size()-1;i+=2){
        v2[sv2[i]].push_back(sv2[i + 1]);
        v2[sv2[i + 1]].push_back(sv2[i]);
    }
    /*//вывод смежностей
    for (int i = 0; i < v2.size(); i++) {
    for (int j = 0; j < v2[i].size(); j++)
            std::cout<<v2[i][j] << " ";
    }
    std::cout<<std::endl;*/

    // СЧИТЫВАНИЕ СГЕНЕРИРОВАННОГО ГРАФА: КОНЕЦ

    //ПОИСК ЦИКЛОВ НАЧАЛО

    struct Node {
    int vert, parent;
    };
    struct Edge {
    int src, dest;
    };
    std::vector<bool> discovered;
    discovered.resize(sv.size());
    discovered[0] = true;
    std::queue<Node> q;
    q.push({ 0, -1 });
    bool check = false;
    while (!q.empty()) {
        Node node = q.front();
        q.pop();
        for (int u : v[node.vert]) {
            if (!discovered[u]) {
                discovered[u] = true;
                q.push({ u, node.vert });
            }
            else if (u != node.parent) {
                check = false;
                break;
            }
        }
        check = true;
    }

    //ПОИСК ЦИКЛОВ КОНЕЦ

    //ИТОГОВАЯ ПРОВЕРКА
    if (verticles==rand_vert and check==1){
         Database::getInstance()->execQuery("UPDATE users SET task3 = task3 + 1 WHERE mail = \"" + email+"\"");
        return "It's a true answer!";
    }
    else return "Wrong answer!";

}

/*!
 * \brief Генерация графа
 * \return Фукнция возвращает QString сгенерированного графа
 */

QByteArray get_task3(){
    QString answer;
    answer.append("Graph:" + '\n');
    // ГЕНЕРАЦИЯ ГРАФА НАЧАЛО
    std::vector<std::vector<int>> rand_gr;
    std::set<int> rand_vert;
    std::set<std::map<int, int>> check_f_rep;
    srand(time(NULL));
    int count_v = rand() % (15 - 1 - 8) + 8;              //ограничения: минимум 8 вершин, максимум 15
    int count_e = rand() % (30 - 1 - 12) + 12;            //ограничения: минимум 12 ребер, максимум 30
    int e = count_e, perv;
    for (int i = 1; i < e; i++) {
        std::vector<int> pairs;
        perv = rand() % (count_v * 10 + 9 - 1 + 11) + 11;
        if (perv % 10 == int(perv / 10)) perv++;
        if (perv % 10 == 0) perv++;
        std::map<int, int> m;
        m.insert(std::pair<int, int>(std::min(perv % 10, int(perv / 10)), std::max(perv % 10, int(perv / 10))));
        if (check_f_rep.count(m) or perv % 10 > count_v or int(perv / 10) > count_v or perv == 99) {
            e++;
            continue;
        }
        pairs.push_back(std::min(perv % 10, int(perv / 10)));
        pairs.push_back(std::max(perv % 10, int(perv / 10)));
        rand_gr.push_back(pairs);
        rand_vert.insert({ std::min(perv % 10, int(perv / 10)),std::max(perv % 10, int(perv / 10)) });
        std::map<int, int> k;
        k.insert(std::pair<int,int>(std::min(perv % 10, int(perv / 10)), std::max(perv % 10, int(perv / 10))));
        check_f_rep.insert(k);
    }
    std::sort(rand_gr.begin(), rand_gr.end());
    /*for (int i = 0; i < rand_gr.size(); i++) {
        for (int j = 0; j < rand_gr[i].size(); j++)
            std::cout << rand_gr[i][j] << " ";
        std::cout << std::endl;
    }*/
    for (int i = 0; i < rand_gr.size(); i++) {
        for (int j = 0; j < rand_gr[i].size(); j++)
            answer.append(QString::number(rand_gr[i][j]) + " ");
        answer.append('\n');
    }
    //for (int i : rand_vert) std::cout << i << " ";
    return answer.toUtf8();

}


QByteArray checktask2(const QString& email,const QString& variant,const QString& answer){

    std::random_device rd;
    std::mt19937 gen(rd());
    QStringList var = variant.split("/");
  int n = var[0].toInt();
  int m = var[1].toInt();
  QStringList pairs = var[2].split(";");
  QVector<std::pair<int, int>> edges;
  for (int i = 0; i < pairs.size();i++)
  {
    int k = QVariant(pairs[i][0]).toInt() - 48;
    qDebug()<< k;
    int l = QVariant(pairs[i][2]).toInt() - 48;
    std::pair<int,int> p;
    p = std::make_pair(k,l);
    edges.push_back(p);
  }


    qDebug() << edges;

    // Создаем матрицу инцидентности и заполняем ее нулями
    QVector<QVector<int>> incidenceMatrix(n, QVector<int>(m, 0));

    // Заполняем матрицу инцидентности
    for (int i = 0; i < m; i++) {
        int startVertex = edges[i].first;
        int endVertex = edges[i].second;
        int startVertexIndex = startVertex ;
        int endVertexIndex = endVertex ;
        incidenceMatrix[startVertexIndex][i] = 1;
        incidenceMatrix[endVertexIndex][i] = -1;
    }

    // Выводим матрицу инцидентности в консоль
    QString matrix;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix.append(QString::number(incidenceMatrix[i][j]) + " ");
        }

    }

    matrix.resize(matrix.size()-1);
    if (matrix == answer){
        return "Правильно";
    }
    else{
        return "Неправильно";
    }


}

QByteArray checktask1(const QString& email,const QString& variant,const QString& answer){

  QStringList var = variant.split("/");
  int n = var[0].toInt();
  int m = var[1].toInt();
  QStringList pairs = var[2].split(";");
  QVector<std::pair<int, int>> edges;
  for (int i = 0; i < pairs.size();i++)
  {
    int k = QVariant(pairs[i][0]).toInt() - 48;
    int l = QVariant(pairs[i][2]).toInt() - 48;
    std::pair<int,int> p;
    p = std::make_pair(k,l);
    edges.push_back(p);
  }

  for (int i = 0; i < edges.size(); i++) {
      int u = edges[i].first;
      int v = edges[i].second;
      graph[u].push_back(v);
      graph[v].push_back(u);
  }
  for (int i = 0; i < n; i++) {
      for (int j : graph[i])
      {
          adjacencyMatrix[i][j] = true;
      }
  }
  QString matrix;
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
          matrix.append(QString::number(adjacencyMatrix[i][j]) + " ");
      }

  }
  qDebug() << matrix;

  matrix.resize(matrix.size()-1);
  if (matrix == answer){
      return "Правильно";
  }
  else{
      return "Неправильно";
  }
}

QByteArray task3(const QString& email){
     return "task3";
};
/*!
 * \brief 4 Задание
 * \param Функция принимает QString e-mail
 * \return Фукнция возвращает QString результат выполнения задания
 */
QByteArray task4(const QString& email){
    QString answer;
    // Задаем случайное количество вершин и ребер
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> vertexDis(4, 7); // от 2 до 10 вершин
    std::uniform_int_distribution<> edgeDis(4, (vertexDis(gen) * (vertexDis(gen) - 1)) / 2); // от 1 до n*(n-1)/2 ребер
    int n = vertexDis(gen); // количество вершин
    int m = edgeDis(gen); // количество ребер
//    answer.append(QString::number(n)+"/");
//    answer.append(QString::number(m)+"/");
    // Создаем список вершин
    QVector<int> vertices(n);
    for (int i = 0; i < n; i++) {
        vertices[i] = i + 1;

    }
    // Создаем список ребер

    QVector<std::pair<int, int>> edges;{

        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < n; j++)
            {
                edges.push_back(std::make_pair(i, j));
            }
        }
    }
    // Создаем матрицу смежности
    QVector<QVector<int>> adjacencyMatrix(n, QVector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j =0 ; j < n; j++) {
             adjacencyMatrix[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
            int startVertex = edges[i].first;
            int endVertex = edges[i].second;
            //int startVertexIndex = startVertex ;
            //int endVertexIndex = endVertex ;
             adjacencyMatrix[startVertex][endVertex] = 1;
             adjacencyMatrix[endVertex][startVertex] = 1;

    }

    // Создаем матрицу инцидентности и заполняем ее нулями
    QVector<QVector<int>> incidenceMatrix(n, QVector<int>(m, 0));

    // Заполняем матрицу инцидентности
    for (int i = 0; i < m; i++) {
        int startVertex = edges[i].first;
        int endVertex = edges[i].second;
        int startVertexIndex = startVertex ;
        int endVertexIndex = endVertex ;
        incidenceMatrix[startVertexIndex][i] = 1;
        incidenceMatrix[endVertexIndex][i] = -1;
    }
    QString rebra;
        rebra.append(QString::number(n)+"/");
        rebra.append(QString::number(m)+"/");
    int k = 0;
    for (auto i:edges) {
        if(k==m){
            break;
        }
        rebra.append(QString::number(i.first) + "-" + QString::number(i.second) + ";");
        k+=1;
    }
    qDebug() << rebra;
    // Выводим матрицу инцидентности в консоль
QString matrix;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix.append(QString::number(incidenceMatrix[i][j]) + " ");
        }
           matrix.remove(matrix1.size()-1,1);
         matrix.append("/");

    }
    qDebug() <<"инциндетности";
    qDebug() << matrix;
    // Выводим матрицу смежности в консоль

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix1.append(QString::number(adjacencyMatrix[i][j]) + " ");
        }
        matrix1.remove(matrix1.size()-1,1);
        matrix1.append("/");

    }
    qDebug() <<"смежности";
    qDebug() << matrix1;


    // Выводим матрицу инцидентности в ответ
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
                answer.append(QString::number(incidenceMatrix[i][j]) + " ");
            }
            answer.remove(matrix1.size()-1,1);
             answer.append("/");
         }

    return answer.toUtf8();


}

QByteArray checktask4(const QString &email, const QString &variant, const QString &answer)
{
        qDebug() << matrix1;
        qDebug() << answer;
       if (matrix1 == answer){
           return "Правильно";
       }
       else{
           return "Неправильно";
       }
     }


