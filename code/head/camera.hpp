#pragma once

#include <utility>


#include "Eigen/Dense"
#include "film.hpp"
#include "ray.hpp"

#define M_PIf 3.14159265358979323846f

class Camera {
public:
    Camera(const Eigen::Vector3f& pos, const Eigen::Vector3f& lookAt, const Eigen::Vector3f& up, float verticalFov, const Eigen::Vector2i& filmRes) : m_Film(filmRes)
	{
        m_Pos = pos;
        /*
		 * TODO: Creat axes for camera here, which concerns m_Forward, m_Right and m_Up variables
		 */
    }

	// Generate camera ray
	// dx and dy is the pixel's coordinate
	Ray generateRay(int dx, int dy)
	{
        /*
		 * TODO: Shoot camera ray here
		 */
    }

    void setPixel(int dx, int dy, Eigen::Vector3f value)
    {
        m_Film.pixelSamples[dy * m_Film.m_Res.x() + dx] = std::move(value);
    }
	
    Eigen::Vector3f m_Pos;
	
    Eigen::Vector3f m_Forward;
    Eigen::Vector3f m_Right;
    Eigen::Vector3f m_Up;
	
    Film m_Film;
};
