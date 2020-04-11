#pragma once
#include <vector>
#include "shape.hpp"
#include "objloader.hpp"
#include "refine.hpp"

class TriangleMesh : public Shape
{
public:
	// number of triangles
	int triangleCount;
	// verteces, normals and indices data
	std::vector<Eigen::Vector3f> out_vertices;
	std::vector<Eigen::Vector3f> out_normals;
	std::vector<int> out_v_index;
	std::vector<int> out_vn_index;
	// uniform grid data
	bool isUniformExisting;
	std::vector<std::vector<int>> grid;
	Eigen::Vector3i gridDim;
	Eigen::Vector3f gridDeltaDist;
	
	explicit TriangleMesh(const Eigen::Vector3f& color, std::string filePos)
		: Shape(color)
	{
		std::vector <Eigen::Vector2f> out_uvs;
		std::vector <int> out_vt_index;
		loadOBJ_index(filePos.c_str(), out_vertices, out_uvs, out_normals, out_v_index, out_vt_index, out_vn_index);
		
		triangleCount = out_v_index.size() / 3;
		
		m_BoundingBox.lb = out_vertices[0].cwiseMin(out_vertices[1]);
		m_BoundingBox.ub = out_vertices[0].cwiseMax(out_vertices[1]);
		for (int i = 2; i < out_vertices.size(); i++)
		{
			m_BoundingBox.lb = m_BoundingBox.lb.cwiseMin(out_vertices[i]);
			m_BoundingBox.ub = m_BoundingBox.ub.cwiseMax(out_vertices[i]);
		}

		isUniformExisting = false;
	}

	// ray intersection with single triangle, result saves in @Interaction
	bool raySingleTriangleIntersection(Interaction& interaction, const Ray& ray, int v0_idx, int v1_idx, int v2_idx)
	{
		/*
		 * TODO: Ray intersection test with single triangle
		 * Note:
		 * 1. If intersected, fill every variable in @Interaction class except for @Interaction.exitDist.
		 * 2. Normals are interpolated using barycentric coordinates.
		 */
	}

	// ray intersection with mesh, result saves in @Interaction
	bool rayIntersection(Interaction& interaction, const Ray& ray) override
	{
		Interaction finalInteraction;
		if (isUniformExisting) {
			/*
			 * TODO: Use uniform grid to handle triangle intersection here
			 * Note: Grid traversal algorithm must be used here.
			 */
		} else {
			for (int i = 0; i < triangleCount; i++) {
				Interaction curInteraction;
				if (raySingleTriangleIntersection(curInteraction, ray, 3 * i, 3 * i + 1, 3 * i + 2)) {
					if (finalInteraction.entryDist == -1 || curInteraction.entryDist < finalInteraction.entryDist) {
						finalInteraction = curInteraction;
					}
				}
			}
		}

		if (finalInteraction.entryDist != -1)
		{
			interaction = finalInteraction;
			return true;
		}
		return false;
	}

	// apply a certain transformation to all vertices, normals and bounding box
	void applyTransformation(const Eigen::Affine3f& t)
	{
		for (int i = 0; i < out_vertices.size(); i++)
		{
			out_vertices[i] = t * out_vertices[i];
		}

		Eigen::Matrix3f tInvTr = t.linear().inverse().transpose();
		for (int i = 0; i < out_normals.size(); i++)
		{
			out_normals[i] = (tInvTr * out_normals[i]).normalized();
		}

		m_BoundingBox.lb = out_vertices[0].cwiseMin(out_vertices[1]);
		m_BoundingBox.ub = out_vertices[0].cwiseMax(out_vertices[1]);
		for (int i = 2; i < out_vertices.size(); i++)
		{
			m_BoundingBox.lb = m_BoundingBox.lb.cwiseMin(out_vertices[i]);
			m_BoundingBox.ub = m_BoundingBox.ub.cwiseMax(out_vertices[i]);
		}
	}

	void subdivision()
	{
		// TODO: Call loop subdivision here
		std::vector<ref::point> P_list(out_vertices.size());
		std::vector<ref::line> L_list;
		std::vector<ref::face> F_list(int(out_v_index.size() / 3));
		ref::build_data_struct(
			out_vertices, out_normals,
			out_v_index, out_vn_index,
			P_list, L_list, F_list);

		std::vector<ref::point> P_list_new;
		std::vector<ref::line> L_list_new;
		std::vector<ref::face> F_list_new;

		
		int division_time = 3;

		// TODO: You can make loop_subdivision a recursive function or call loop_subdivision with for loop.
		ref::loop_subdivision(
			P_list, L_list, F_list,
			P_list_new, L_list_new, F_list_new);
		
		// TODO: Change out_vertices, out_normals, out_v_index and out_vn_index with the information in P_list and F_list

		// Finally, update the new size
		triangleCount = out_v_index.size() / 3;
	}


	void buildUniformGrid() {
		/*
		 * TODO: Build uniform grid here
		 */

		// Don't forget to change isUniformExisting to true after building the grid
		isUniformExisting = true;
	}

};
