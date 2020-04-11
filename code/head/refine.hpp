#pragma once
#include <vector>
//#include "../3rdLibs/glm/glm/glm.hpp"
#include "Eigen/Dense"
#include <algorithm>

//////////////////////////////////////////////////////////////////////////////////////////////
// You should try to reduce the time complexity. For each time of loop subdivision (divide  //
// once), the time complexity of your program should not be lower than O(p^2+f*l) (p:number //
// of points, f: number of faces, l: number of lines). And try to explain how you reduce the//
// time complexity in you report and video.                                                 //
//                                                                                          //
// The following is a reference for you to do loop subdivision.                             //
//////////////////////////////////////////////////////////////////////////////////////////////
namespace ref {
	class point {
	public:
		Eigen::Vector3f pos;
        Eigen::Vector2f uv;	// you can ignore uv
        Eigen::Vector3f normal;	
        //one pos may have different, if you want to use exact value, you should store this
        //std::vector<Eigen::Vector2f> uv;
        //std::vector<Eigen::Vector3f> normal;
        std::vector<int> n_face;
        std::vector<int> n_point;
        std::vector<int> b_point;
        std::vector<int> n_line;
        bool is_border;
        point();
        ~point();
	};

	class face {
    public:
        int v[3];   //We have to use index, instead of point itself;
        //std::vector<Eigen::Vector2f> n_line;
        std::vector<int> n_line;
	};

	class line {
    public:
        int v1;     //We have to use index, instead of point itself;
        int v2;
        std::vector<int> n_face;
        bool is_border;
        line();
        ~line();
	};
    
    // Decide whether a line is boundary: Find adj faces of one of the two points, and check whether any of them used the other point.
    // Use face as the iterator of loop to find lines
    
    void build_data_struct(
        std::vector < Eigen::Vector3f > out_vertices,
        std::vector < Eigen::Vector3f > out_normals,
        std::vector < int > out_v_index,
        std::vector < int > out_vn_index,
        std::vector<ref::point>& P_list,
        std::vector<ref::line>& L_list,
        std::vector<ref::face>& F_list);
    

    // Loop subdivision
    void loop_subdivision(
        std::vector<ref::point> P_list,
        std::vector<ref::line> L_list,
        std::vector<ref::face> F_list,
        std::vector<ref::point>& P_list_new,
        std::vector<ref::line>& L_list_new,
        std::vector<ref::face>& F_list_new);

    void make_face(
        std::vector<ref::point> P_list,
        std::vector<ref::face> F_list,
        std::vector<Eigen::Vector3f>& points, 
        std::vector<Eigen::Vector3f>& normals, 
        std::vector<Eigen::Vector2f>& uvs
    );
}
//line will decide which point is boundary
ref::point::point()
{
    this->is_border = false;
}
ref::point::~point()
{
    
}
//face will decide which line is not boundary
ref::line::line()
{
    this->is_border = true;
}
ref::line::~line()
{
    
}

void ref::build_data_struct(
    std::vector < Eigen::Vector3f > out_vertices,
    std::vector < Eigen::Vector3f > out_normals,
    std::vector < int > out_v_index,
    std::vector < int > out_vn_index,
    std::vector<ref::point>& P_list,
    std::vector<ref::line>& L_list,
    std::vector<ref::face>& F_list)
{
    
    return;
}

void ref::loop_subdivision(
    std::vector<ref::point> P_list,
    std::vector<ref::line> L_list,
    std::vector<ref::face> F_list,
    std::vector<ref::point>& P_list_new,
    std::vector<ref::line>& L_list_new,
    std::vector<ref::face>& F_list_new)
{
    

    return;
}


void ref::make_face(
        std::vector<ref::point> P_list,
        std::vector<ref::face> F_list,
        std::vector<Eigen::Vector3f>& points, 
        std::vector<Eigen::Vector3f>& normals, 
        std::vector<Eigen::Vector2f>& uvs)
{
	return;
}
		

