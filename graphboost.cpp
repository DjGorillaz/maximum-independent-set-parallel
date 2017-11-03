#include "graphboost.h"

#include <iostream>
#include <boost/thread.hpp>
#include "graphmatrix.h"

unsigned GetTickCount()
{
    struct timeval tv;
    if(gettimeofday(&tv, NULL) != 0)
        return 0;
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

GraphBoost::GraphBoost(int N): vNumber(N), t(0)
{
    //Generate graph
    srand(time(NULL));
    vector< pair<int, int> > edges;
    for(int i = 0; i < N; ++i)
    {
        for(int j = i+1; j < N; ++j)
        {
            //Graph connectivity = 60%
            if(rand() % 10 < 6)
                edges.push_back(make_pair(i,j));
        }
    }

    graph = Graph(edges.begin(), edges.end(), vNumber);

    graph_traits<Graph>::vertex_iterator start, end;
    map = get(vertex_name,graph);

    //Create N-length vector for each vertex
    boost::tie(start, end) = vertices(graph);
    for(; start != end; ++start)
    {
        map[*start].resize(vNumber, boost::make_tuple(false, false));
    }

    vSetCount.resize(vNumber, 0); //This vector contains number of vertices after each pass of algorithm
}

void GraphBoost::printGraph()
{
    graph_traits<Graph>::vertex_descriptor vertex;
    graph_traits<Graph>::edge_iterator start, end;
    boost::tie(start, end) = edges(graph);
    int prevVertex = 0;
    for (; start != end; ++ start)
    {
        vertex = source(*start, graph);
        if (prevVertex != vertex) cout << endl;
        cout << *start << " ";
        prevVertex = vertex;
    }
    cout << endl << endl;
}

void GraphBoost::run(int proc)
{
    t = GetTickCount();

    thread_group threadGroup;
    graph_traits<Graph>::vertex_iterator start, end;
    boost::tie(start, end) = vertices(graph);

    int perProc = vNumber/proc;
    int l = 0;
    int r = perProc;
    //Parallelization of task
    for (int i = 0; i < proc; ++i)
    {
        if (i == (proc - 1)) r = vNumber - 1;
        thread* th = new thread(&GraphBoost::findThread, this, l, r);
        threadGroup.add_thread(th);
        l = r + 1;
        r = r + perProc;
    }
    threadGroup.join_all();
}

void GraphBoost::findMaxIndependentSet(graph_traits<Graph>::vertex_iterator startVertex, int i)
{
    if(get<0>(map[*startVertex][i]) == true) //If the vertex is already viewed
        return;
    get<0>(map[*startVertex][i]) = true; //The vertex is viewed
    get<1>(map[*startVertex][i]) = true; //The vertex is already in set
    vSetCount[i] += 1; //Increase size of independent set by 1

    graph_traits<Graph>::adjacency_iterator adjStart, adjEnd; //Neighbors of startVertex
    boost::tie(adjStart, adjEnd) = adjacent_vertices(*startVertex, graph);
    //Look through all neighbors
    for(; adjStart != adjEnd; ++adjStart)
    {
        if(get<0>(map[*adjStart][i]) == false) //The vertex isn't viewed
        {
          get<0>(map[*adjStart][i]) = true; //The vertex is viewed
          get<1>(map[*adjStart][i]) = false; //The vertex is not in set
        }
    }

    //Look through all neighbors
    boost::tie(adjStart, adjEnd) = adjacent_vertices(*startVertex, graph);
    for(; adjStart != adjEnd; ++adjStart)
    {
        //Look through all neighbors of neighbors
        graph_traits<Graph>::adjacency_iterator adj2Start, adj2End;
        boost::tie(adj2Start, adj2End) = adjacent_vertices(*adjStart, graph);
        for(; adj2Start != adj2End; ++adj2Start)
        {
            //Recursive call
            findMaxIndependentSet(graph_traits<Graph>::vertex_iterator(*adj2Start), i);
        }
    }
}

void GraphBoost::findThread(int first, int second)
{
    graph_traits<Graph>::vertex_iterator start, end;
    boost::tie(start, end) = vertices(graph);
    start += first;
    //The range of vertices is set for each processor
    for(int i = first; i <= second; ++start, ++i)
    {
        findMaxIndependentSet(start, i);
    }
}

void GraphBoost::printResult()
{
    //Find maximal indpendent set
    int maxCount = 0, index = 0;
    for(int i = 0; i < vSetCount.size(); ++i)
    {
        if(vSetCount[i] > maxCount)
        {
            maxCount = vSetCount[i];
            index = i;
        }
    }

    t = GetTickCount() - t;

    //Print result
    cout << "Greedy algorithm" << endl;
    cout << "Time: " << t << " ms" << endl;
    cout << "Size: " << maxCount << " vertices" << endl;
    cout << "Result: ( ";
    graph_traits<Graph>::vertex_iterator start, end;
    boost::tie(start, end) = vertices(graph);
    for(; start != end; ++start)
    {
        if(get<1>(map[*start][index]) == true) //Is in set
            cout << *start << " ";
    }
    cout<<")" << endl << endl;
}

GraphBoost::GraphBoost(GraphMatrix& gr): vNumber(gr.vNumber), t(0)
{
    //Generate graph
    srand(time(NULL));
    vector< pair<int, int> > edges;
    for(int i = 0; i < vNumber; ++i)
    {
        for(int j = i+1; j < vNumber; ++j)
        {
            if(gr.graph[i][j] == true)
                edges.push_back(make_pair(i,j));
        }
    }

    graph = Graph(edges.begin(), edges.end(), vNumber);
    graph_traits<Graph>::vertex_iterator start, end;
    map = get(vertex_name,graph);

    //Create N-length vector for each vertex
    boost::tie(start, end) = vertices(graph);
    for(; start != end; ++start)
    {
        map[*start].resize(vNumber, boost::make_tuple(false, false));
    }
    vSetCount.resize(vNumber, 0); //This vector contains number of vertices after each pass of algorithm
}
