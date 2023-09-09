#include "Obj.hpp"

bool Obj::Intersection(Section a) { 
    if (intersectionSectionAndSection(Section{posRect.left, posRect.top, posRect.left + posRect.width, posRect.top + posRect.height}, a) ||
        intersectionSectionAndSection(Section{posRect.left + posRect.width, posRect.top, posRect.left, posRect.top + posRect.height}, a))
        return true;
    return false;
}

bool Obj::isPointOnTheSection(sf::Vector2f point, Section sect){
    // Нужна проверка, если линия вертикальная, то есть если ray.direction.x == 0
    if (std::abs(sect.x1 - sect.x2) <= 0.1 && std::abs(sect.x1 - sect.x2) >= -0.1){
        // Если точка принадлежит прямой
        if (point.x + 0.1 >= sect.x1 && point.x - 0.1 <= sect.x1){
            // Если точка принадлежит отрезку
            if ((point.y >= sect.y1 && point.y <= sect.y2) || (point.y >= sect.y2 && point.y <= sect.y1)){
                return true;
            }
        }
    }
    else {
        float k = (sect.y1 - sect.y2) / (sect.x1 - sect.x2);
    	float b = sect.y1 - k * sect.x1;
    	float assumedY = k * point.x + b;
    	float assumedX = (point.y - b) / k;
    	// Если координаты У совпадают у точки и прямой
    	if (point.y + 0.1 >= assumedY && point.y - 0.1 <= assumedY)
    	{   
    	    if ((point.y >= sect.y1 && point.y <= sect.y2) || (point.y >= sect.y2 && point.y <= sect.y1)){
    	        if ((point.x >= sect.x1 && point.x <= sect.x2) || (point.x >= sect.x2 && point.x <= sect.x1))
    	            return true;
    	    }    
    	}
    	
    }
	
	return false;
}
bool Obj::intersectionSectionAndSection(const Section sect1, const Section sect2){
    // Если отрезок1 и отрезок2 вертикальные
    if (std::abs(sect1.x1 - sect1.x2) <= 0.1 && std::abs(sect1.x1 - sect1.x2) >= -0.1 && 
    std::abs(sect2.x1 - sect2.x2) <= 0.1 && std::abs(sect2.x1 - sect2.x2) >= -0.1)
        return false;
    // Если отрезок1 вертикальный
	else if (std::abs(sect1.x1 - sect1.x2) <= 0.1 && std::abs(sect1.x1 - sect1.x2) >= -0.1){
	    float kS = (sect2.y1 - sect2.y2) / (sect2.x1 - sect2.x2);
    	float bS = sect2.y1 - kS * sect2.x1;
    	float intersectY = kS * sect1.x1 + bS;
    	sf::Vector2f p{sect1.x1, intersectY};
    	if (isPointOnTheSection(p, sect1) && isPointOnTheSection(p, sect2))
    	    return true;
	}
	// Если отрезок2 вертикальный
	else if (std::abs(sect2.x1 - sect2.x2) <= 0.1 && std::abs(sect2.x1 - sect2.x2) >= -0.1)
	{
	    float kS = (sect1.y1 - sect1.y2) / (sect1.x1 - sect1.x2);
    	float bS = sect1.y1 - kS * sect1.x1;
    	float intersectY = kS * sect2.x1 + bS;
    	sf::Vector2f p{sect2.x1, intersectY};
    	if (isPointOnTheSection(p, sect1) && isPointOnTheSection(p, sect2))
    	    return true;
	}
	else{
	    float kS1 = (sect1.y1 - sect1.y2) / (sect1.x1 - sect1.x2);
    	float bS1 = sect1.y1 - kS1 * sect1.x1;
    	float kS2 = (sect2.y1 - sect2.y2) / (sect2.x1 - sect2.x2);
    	float bS2 = sect2.y1 - kS2 * sect2.x1;
        // 	std::cout << kR << ' ' << bR << ' '
        // 	<< kS << ' ' << bS << std::endl;
    	if (std::abs(kS1 - kS2) >= 0.1 || std::abs(kS1 - kS2) <= -0.1){
    	    float intersectX = (bS2 - bS1) / (kS1 - kS2);
        	float intersectY = kS1 * intersectX + bS1;
        	sf::Vector2f p{intersectX, intersectY};
        	if (isPointOnTheSection(p, sect1) && isPointOnTheSection(p, sect2))
        	    return true;
    	}
	}
	return false;
}

bool Obj::assumeCollideX(const float x, sf::FloatRect other)  {
    bool flag = false;
    posRect.left += x;
    if (posRect.intersects(other))
        flag = true;
    posRect.left -= x;
    return flag;
}

bool Obj::assumeCollideY(const float y, sf::FloatRect other){
    bool flag = false;
    posRect.top += y;
    if (posRect.intersects(other))
        flag = true;
    posRect.top -= y;
    return flag;
}
