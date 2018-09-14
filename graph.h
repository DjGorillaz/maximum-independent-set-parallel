
#pragma once

// #include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/adjacency_list.hpp>

// typedef adjacency_list<vecS, vecS, undirectedS, property<vertex_name_t, vector<boost::tuple<bool,bool>> > > Graph;
// typedef property_map<Graph, vertex_name_t>::type Map;

namespace MaximumIndependentSet
{
    //using Matrix = boost::adjacency_matrix<boost::undirectedS>;
    using GraphBoost =  boost::adjacency_list<
        boost::vecS,
        boost::vecS,
        boost::undirectedS
        // boost::no_property
        //boost::property<
         //   boost::vertex_name_t,
         //   std::vector<boost::tuple<bool,bool>>
        //>
    >;

    class Graph//: public Graph
    {
    public:
        Graph(int n, float conn);
        void print() const;

        friend class Finder;

    private:
        int nVertices;      //Number of vertices
        float connectivity; //Graph connectivity, %
        GraphBoost graphB; 
    };
}
