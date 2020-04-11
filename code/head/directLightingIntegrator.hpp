#pragma once
#include "integrator.hpp"

class DirectLightingIntegrator : public Integrator
{
public:
	// blinn phong parameters
	float shininess = 16.0f;
	float lightPower = 15.0f;
	Eigen::Vector3f ambientColor = Eigen::Vector3f(0.1, 0.1, 0.1);
	Eigen::Vector3f specColor = Eigen::Vector3f(1.0, 1.0, 1.0);
	
	DirectLightingIntegrator(Scene* scene, Camera* camera)
		: Integrator(scene, camera)
	{
	}

	// main render loop
	void render() override
	{
		for (int dx = 0; dx < camera->m_Film.m_Res.x(); dx++)
		{
			for (int dy = 0; dy < camera->m_Film.m_Res.y(); dy++)
			{
				Ray ray = camera->generateRay(dx, dy);
				Interaction surfaceInteraction;
				if (scene->intersection(&ray, surfaceInteraction))
				{
					camera->setPixel(dx, dy, radiance(&surfaceInteraction, &ray));
				}
			}
		}
	}

	// radiance of a specific point
	Eigen::Vector3f radiance(Interaction* interaction, Ray * ray) override
	{
		/*
		 * TODO (1): Shoot shadow ray to form shadow
		 * TODO (2): If not in shadow, use Phong reflection model to determine pixel color
		 */
	}
};