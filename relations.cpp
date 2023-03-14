    /***********************************************************/
    #include <iostream>
    using namespace std;

    #include <limits>

    /***********************************************************/

    #define SIZE 10

    class Graph {
    public:

        Graph();
        // добавление вершины
        void addVertex(int vnumber);
        // добавление ребра
        void addEdge(int v1, int v2, int weight);
        // удаление вершины
        void delVertex(int vnumber);
        // удаление ребра
        void delEdge(int v1, int v2);

        void show();

        void getRelations(Graph* r, int depth, int init, int curr, int* visited);

        void relations(Graph* relation);

    private:
        bool edgeExists(int v1, int v2);
        bool vertexExists(int v);

        // void depthInner(int current, bool visited[]);

        int matrix[SIZE][SIZE]; // матрица смежности

        int vertexes[SIZE]; // хранилище вершин
        int vertexCount; // количество добавленных вершин
    };

    /***********************************************************/

    Graph::Graph() {
        for (int i = 0;i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                matrix[i][j] = 0;
        vertexCount = 0;
    }

    /***********************************************************/

    // добавление вершины
    void Graph::addVertex(int vnumber)
    {
        vertexes[vertexCount] = vnumber;
        vertexCount++;
    }

    /***********************************************************/

    // добавление ребра
    void Graph::addEdge(int v1, int v2, int weight)
    {
        matrix[v1][v2] = weight;
        matrix[v2][v1] = weight;
    }

    /***********************************************************/

    // проверка существования ребра
    bool Graph::edgeExists(int v1, int v2)
    {
        return matrix[v1][v2] > 0;
    }

    /***********************************************************/

    // проверка существования вершины
    bool Graph::vertexExists(int v)
    {
        for (int i = 0; i < vertexCount;i++)
            if (vertexes[i] == v)
                return true;
        return false;
    }

    /***********************************************************/

    void Graph::delEdge(int v1, int v2)
    {
        matrix[v1][v2] = 0;
        matrix[v2][v1] = 0;
    };

    /***********************************************************/

    void Graph::delVertex(int vnumber)
    {
        vertexes[vnumber] = 0;
        for (int i = 0; i < SIZE; i++)matrix[vnumber][i] = 0;
        for (int i = 0; i < SIZE; i++)matrix[i][vnumber] = 0;
    };

    /***********************************************************/
   /*
    void show_route(int cntr, int* route)
    {
        cout << "route";
        for (int i = 0; i < cntr; i++) cout << " " << route[i];
        cout << endl;
    };

    void show_found(int cntr, int* route, int dist)
    {
        cout << "dist = " << dist;
        for (int i = 0; i < cntr; i++) cout << " " << route[i];
        cout << endl;
    };

    void show_visit(int cntr, bool* visit)
    {
        cout << "visit";
        for (int i = 0; i < cntr; i++) cout << " " << visit[i];
        cout << endl;
    };

    */

    /***********************************************************/

    void Graph::show()
    {
        cout << "x";
        for (int i = 0; i < vertexCount; i++)cout << " " << i;
        cout << endl;

        for (int i = 0; i < vertexCount; i++)
        {
            cout << i << " ";
            for (int j = 0; j < vertexCount; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        };
        cout << endl;
    };

    /***********************************************************/

    void Graph::getRelations(Graph* r, int depth, int init, int curr, int* visited)
    {
        int d = 0;
        visited[curr] = true;                   // it ia visited
        if (depth == 3)return;                  // max. deoth
        for (int i = 0; i < vertexCount; i++)   // for each node 
        {
            if (!visited[i])                    // not visited?
            {
                d = matrix[curr][i];            // distance
                if (d != 0)                     // is it neighboring?
                {
                    r->addEdge(init, i, d);     // add 
                    // r->show();
                    getRelations(r, depth + 1, init, i, visited);   // go further
                };
            };
        };
        visited[curr] = false;                  // now it is not visited
    };

    /***********************************************************/

    void Graph::relations(Graph* r)
    {
        int d; int visited[SIZE];
        for (int i = 0; i < SIZE; i++)
            visited[i] = false;
        for (int i = 0; i < vertexCount; i++)
            r->addVertex(i);
        for (int i = 0; i < vertexCount; i++)
            getRelations(r, 0, i, i, visited);
    };

    /***********************************************************/

    int main()
    {
        Graph g;
        Graph r;

#define LENG    8   // build a long circle

        for (int i = 0; i < LENG; i++)
            g.addVertex(0);
        for (int i = 0; i < LENG; i++)
            g.addEdge(i, (i + 1) % LENG, 1);

        cout << "initial graph" << endl;

        g.show();

        g.relations(&r);

        cout << "relation graph" << endl;

        r.show();

      
    }

    /***********************************************************/

