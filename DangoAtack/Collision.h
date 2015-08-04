#pragma once
#include "Common.h"

class Collision
{
public :
	// ‰~’Œ‚Ç‚¤‚µ‚Ì“–‚½‚è”»’è
	static bool HitCylinder(glm::vec3 pos1, float r1, float h1, glm::vec3 pos2, float r2, float h2);

	// ‹…‚Ç‚¤‚µ‚Ì“–‚½‚è”»’è
	static bool HitSphere(glm::vec3 pos1, float r1, glm::vec3 pos2, float r2);

	// AABB“–‚½‚è”»’è
	static bool HitAABB(glm::vec3 pos1, glm::vec3 size1, glm::vec3 pos2, glm::vec3 size2);

	// ü•ª‚Æ•½–Ê‚Ì“–‚½‚è”»’è
	static bool HitLineVSPlane(glm::vec3 point1, glm::vec3 point2, glm::vec3 planePos, glm::vec3 normal);

	// ü•ª‚Æƒ|ƒŠƒSƒ“‚Ì“–‚½‚è”»’è
	static bool HitLineVSPolygon(glm::vec3 point1, glm::vec3 point2, Polygon polygon);

	// ü•ª‚Æƒ|ƒŠƒSƒ“‚ÌŒğ“_‚ğ‹‚ß‚é
	static glm::vec3 CrossPoint(glm::vec3 point1, glm::vec3 point2, Polygon polygon);

	// ‹…‚Æƒ|ƒŠƒSƒ“‚Ì“–‚½‚è”»’è
	static bool HitSphereVSPolygon(glm::vec3 pos, float r, Polygon polygon);
};

