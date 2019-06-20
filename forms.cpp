#include <cmath>
#include <gl\glew.h>
#include <SDL_opengl.h>
//#include <gl\glu.h> // Deja inclus dans glew.h

#include <SDL.h>
#include "forms.h"
#include "Project_App3/physics.h"

using namespace std;


void Form::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
}


void Form::render()
{
    // Point of view for rendering
    // Common for all Forms
    Vector3 org = anim->getPosition();
    glTranslated(org.x, org.y, org.z);
    glColor3f(col.r, col.g, col.b);

	Vector3 scale = anim->getScale();
	glScaled(scale.x, scale.y, scale.z);
}


Sphere::Sphere(double r, Color cl)
{
    radius = r;
    col = cl;
}


void Sphere::update(double delta_t)
{

}


void Sphere::render()
{
    GLUquadric *quad;
    quad = gluNewQuadric();
	Form::render();
	gluSphere(quad, radius, 30, 20);
    gluDeleteQuadric(quad);
}


Cube_face::Cube_face(Vector3 v1, Vector3 v2, Vector3 org, double l, double w, Color cl)
{
    vdir1 = 1.0 / v1.norm() * v1;
    vdir2 = 1.0 / v2.norm() * v2;
    anim->setPosition(org);
    length = l;
    width = w;
    col = cl;
}


void Cube_face::update(double delta_t)
{
    // Do nothing, no physics associated to a Cube_face
}


void Cube_face::render()
{
    Point p1 = Point();
    Point p2 = p1, p3, p4 = p1;
    p2.translate(length*vdir1);
    p3 = p2;
    p3.translate(width*vdir2);
    p4.translate(width*vdir2);

    Form::render();
    glBegin(GL_QUADS);
    {
        glColor3f(1,1,0);
        glVertex3d(p1.x, p1.y, p1.z);
        glColor3f(0,1,1);
        glVertex3d(p2.x, p2.y, p2.z);
        glColor3f(1,0,1);
        glVertex3d(p3.x, p3.y, p3.z);
        glColor3f(0,1,0);
        glVertex3d(p4.x, p4.y, p4.z);
    }
    glEnd();
}

void Axis::update(double delta_t)
{
	// Do nothing, no physics associated to a Cube_face
}

Axis::Axis()
{
	arrowY = make_shared<Arrow>(Vector3(0, 1, 0), GREEN);
	arrowX = make_shared<Arrow>(Vector3(1, 0, 0), RED);
	arrowZ = make_shared<Arrow>(Vector3(0, 0, 1), BLUE);
}

void Axis::render()
{
	arrowY->setAnim(anim);
	arrowY->render();

	glPopMatrix();
	glPushMatrix();

	arrowX->setAnim(anim);
	arrowX->render();

	glPopMatrix();
	glPushMatrix();

	arrowZ->setAnim(anim);
	arrowZ->render();
}


void Plane::update(double delta_t)
{
	// Do nothing, no physics associated to a Cube_face
}


void Plane::render()
{
	Vector3 org = anim->getPosition();
	glTranslated(org.x - length / 2.0, org.y, org.z - width / 2.0);
	glColor3f(col.r, col.g, col.b);

	Vector3 scale = anim->getScale();
	glScaled(scale.x, scale.y, scale.z);

	Point p1(0, 0, 0);
	Point p4(length, 0, 0);
	Point p2(0, 0, width);
	Point p3(length, 0, width);

	glBegin(GL_QUADS);
	{
		//glColor3f(1, 1, 0);
		glVertex3d(p1.x, p1.y, p1.z);
		//glColor3f(0, 1, 1);
		glVertex3d(p2.x, p2.y, p2.z);
		//glColor3f(1, 0, 1);
		glVertex3d(p3.x, p3.y, p3.z);
		//glColor3f(0, 1, 0);
		glVertex3d(p4.x, p4.y, p4.z);
	}
	glEnd();
}

Vector3& Plane::getNormal()
{
	Vector3 p1(anim->getPosition().x - length / 2.0, anim->getPosition().y, anim->getPosition().z - width / 2.0);
	Vector3 p3(anim->getPosition().x + length / 2.0, anim->getPosition().y, anim->getPosition().z - width / 2.0);
	Vector3 p2(anim->getPosition().x - length / 2.0, anim->getPosition().y, anim->getPosition().z + width / 2.0);
	Vector3 dir = (p2 - p1) ^ (p3 - p1);
	return dir;
}



void Arrow::update(double delta_t)
{
	// Do nothing, no physics associated to a Cube_face
}

void Arrow::render()
{
	Form::render();
	Vector3 to = dirFromOrigin;
	Vector3 org = anim->getPosition();


	glTranslated(org.x, org.y, org.z);

	// Draw the line
	glBegin(GL_LINES);
	{
		glVertex3d(0, 0, 0);
		glVertex3d(to.x, to.y, to.z);
	}
	glEnd();

	glTranslated(to.x, to.y, to.z);

	// Get the angle of rotation of the cap
	double L = to.norm();
	if ((to.x != 0.0) || (to.y != 0.0)) {
		glRotated(atan2(to.y, to.x) / RADPERDEG, 0.0, 0.0, 1.0);
		glRotated(atan2(sqrt(to.x * to.x + to.y * to.y), to.z) / RADPERDEG, 0.0, 1.0, 0.0);
	}
	else if (to.z < 0) {
		glRotated(180, 1.0, 0.0, 0.0);
	}

	// Draw the cap
	GLUquadric *quad = gluNewQuadric();
	gluCylinder(quad, 0.05, 0, 0.1, 20, 1);
	gluDeleteQuadric(quad);

	//glTranslated(org.x - to.x, org.y - to.y, org.z - to.z);
}



void Ray::update(double delta_t)
{

}

void Ray::render()
{

	Form::render();

	// Draw the line
	glBegin(GL_LINES);
	{
		glVertex3d(pos1.x, pos1.y, pos1.z);
		glVertex3d(pos2.x, pos2.y, pos2.z);
	}
	glEnd();
}





///////////////////////////////////
///////////		GLASS	///////////
///////////////////////////////////
Verre::Verre(double hei, double rayB, double rayT, Color coGob, Color coLiq)
{
	height = hei;
	rayBottom = rayB;
	rayTop = rayT;
	col = RED;
	colorGobelet = coGob;
	colorLiquide = coLiq;
}


void Verre::update(double delta_t)
{
	// Complete this part
}


void Verre::render()
{

	glPopMatrix();
	glPushMatrix();

	// liquide
	Liquide liquide = Liquide(height - 0.005, rayBottom - 0.002, rayTop - 0.002, colorLiquide);
	// Liquide(double hei, double rayB, double rayT, Color co)
	auto animLiquide = make_shared<Animation>(anim->getPosition().x,
		anim->getPosition().y,
		anim->getPosition().z);
	liquide.setAnim(animLiquide);
	liquide.render();

	glPopMatrix();
	glPushMatrix();

	// gobelet
	Gobelet gobelet = Gobelet(height, rayBottom, rayTop, colorGobelet);
	// Gobelet(double hei, double rayB, double rayT, Color co)
	auto animGobelet = make_shared<Animation>(anim->getPosition().x,
		anim->getPosition().y,
		anim->getPosition().z);
	gobelet.setAnim(animGobelet);
	gobelet.render();

	glPopMatrix();
	glPushMatrix();
}


///////////////////////////////////
///////////		LIQUIDE	///////////
///////////////////////////////////
Liquide::Liquide(double hei, double rayB, double rayT, Color co)
{
	height = hei;
	rayBottom = rayB;
	rayTop = rayT;
	col = co;
}


void Liquide::update(double delta_t)
{
	// Complete this part
}


void Liquide::render()
{
	// create cilynder
	GLUquadric* params;
	params = gluNewQuadric();

	// set possition
	glTranslated(anim->getPosition().x, anim->getPosition().y, anim->getPosition().z);
	glRotated(90, -1, 0, 0);
	glColor3f(col.r, col.g, col.b);

	gluQuadricDrawStyle(params, GLU_FILL);
	//gluQuadricTexture(params, GL_TRUE);

	gluCylinder(params, rayBottom, rayTop, height, 20, 1);
	//gluCylinder(GLUquadric* params,base,top,height,slices,stacks);
	gluDeleteQuadric(params);

}



///////////////////////////////////
///////////		GOBELET	///////////
///////////////////////////////////
Gobelet::Gobelet(double hei, double rayB, double rayT, Color co)
{
	height = hei;
	rayBottom = rayB;
	rayTop = rayT;
	col = co;
}


void Gobelet::update(double delta_t)
{
	// Complete this part
}


void Gobelet::render()
{
	// create cilynder
	GLUquadric* params;
	params = gluNewQuadric();

	// set possition
	glTranslated(anim->getPosition().x, anim->getPosition().y, anim->getPosition().z);
	glRotated(90, -1, 0, 0);
	glColor3f(col.r, col.g, col.b);

	gluQuadricDrawStyle(params, GLU_LINE);

	gluCylinder(params, rayBottom, rayTop, height, 20, 1);
	//gluCylinder(GLUquadric* params,base,top,height,slices,stacks);
	gluDeleteQuadric(params);
}







///////////////////////////////
/////////	TABLE	///////////
///////////////////////////////
Table::Table(double heiTotal, double heiTray, double len, double wi, double wiFoot)
{
	heightTotal = heiTotal;
	heightTray = heiTray;
	lenght = len;
	width = wi;
	widthFoot = wiFoot;
}

void Table::update(double delta_t)
{
	// Complete this part
}

void Table::render()
{
	glPopMatrix();
	glPushMatrix();
	
	// pied
	Parallelepipede piedTable = Parallelepipede(lenght, width, (heightTotal - heightTray), RED);
	//Parallelepipede(double len, double wid, double hei, Color co);
	auto animPiedTable = make_shared<Animation>(anim->getPosition().x,
		anim->getPosition().y,
		anim->getPosition().z);
	piedTable.setAnim(animPiedTable);
	piedTable.render();

	glPopMatrix();
	glPushMatrix();
	
	// plateau
	Parallelepipede plateau = Parallelepipede(lenght, width, heightTray, GREEN);
	auto animPlateau = make_shared<Animation>(anim->getPosition().x,
		anim->getPosition().y + heightTotal - heightTray,
		anim->getPosition().z);
	plateau.setAnim(animPlateau);
	plateau.render();

	glPopMatrix();
	glPushMatrix();

}


///////////////////////////////
/////////	PERSONNAGE	///////////
///////////////////////////////
Personnage::Personnage()
{

}

void Personnage::update(double delta_t)
{
	// Complete this part
}

void Personnage::render()
{
	glPopMatrix();
	glPushMatrix();

	double rayonTete = 0.15;
	double largeurBras = 0.1;
	double hauteurBras = 0.5;
	double largeurJambe = 0.2;
	double hauteurJambe = 0.8;
	double largeurTronc = 0.5;
	double hauteurTronc = 0.5;
	double hauteurBassin = 0.25;
	double epaisseur = 0.3;

	Color couleurJambe = BLUE;
	Color couleurBassin = BROWN;
	Color couleurTronc = PURPLE;
	Color couleurPeau = SKIN;

	// jambe gauche
	// Parallelepipede(double len, double wid, double hei, Color co)
	Parallelepipede jambeGauche = Parallelepipede(epaisseur, largeurJambe, hauteurJambe, couleurJambe);
	auto animJambeGauche = make_shared<Animation>(anim->getPosition().x,
		anim->getPosition().y,
		anim->getPosition().z);
	jambeGauche.setAnim(animJambeGauche);
	jambeGauche.render();

	glPopMatrix();
	glPushMatrix();

	// jambe droite
	Parallelepipede jambeDroite = Parallelepipede(epaisseur, largeurJambe, hauteurJambe, couleurJambe);
	auto animJambeDroite = make_shared<Animation>(anim->getPosition().x,
		anim->getPosition().y,
		anim->getPosition().z + largeurTronc - largeurJambe);
	jambeDroite.setAnim(animJambeDroite);
	jambeDroite.render();

	glPopMatrix();
	glPushMatrix();

	// bassin
	Parallelepipede bassin = Parallelepipede(epaisseur, largeurTronc, hauteurBassin, couleurBassin);
	auto animBassin = make_shared<Animation>(anim->getPosition().x,
		anim->getPosition().y + hauteurJambe,
		anim->getPosition().z);
	bassin.setAnim(animBassin);
	bassin.render();

	glPopMatrix();
	glPushMatrix();

	// tronc
	Parallelepipede tronc = Parallelepipede(epaisseur, largeurTronc, hauteurTronc, couleurTronc);
	auto animTronc = make_shared<Animation>(anim->getPosition().x,
		anim->getPosition().y + hauteurJambe + hauteurBassin,
		anim->getPosition().z);
	tronc.setAnim(animTronc);
	tronc.render();

	glPopMatrix();
	glPushMatrix();

	// bras gauche
	Parallelepipede brasGauche = Parallelepipede(epaisseur, largeurBras, hauteurBras, couleurPeau);
	auto animBrasGauche = make_shared<Animation>(anim->getPosition().x,
		anim->getPosition().y + hauteurJambe + hauteurBassin,
		anim->getPosition().z - largeurBras);
	brasGauche.setAnim(animBrasGauche);
	brasGauche.render();

	glPopMatrix();
	glPushMatrix();

	// bras droit
	Parallelepipede brasDroit = Parallelepipede(epaisseur, largeurBras, hauteurBras, couleurPeau);
	auto animBrasDroit = make_shared<Animation>(anim->getPosition().x,
		anim->getPosition().y + hauteurJambe + hauteurBassin,
		anim->getPosition().z + largeurTronc);
	brasDroit.setAnim(animBrasDroit);
	brasDroit.render();

	glPopMatrix();
	glPushMatrix();

	// tete
	// Sphere(double r, Color cl)
	Sphere tete = Sphere(rayonTete, couleurPeau);
	auto animTete = make_shared<Animation>((anim->getPosition().x + rayonTete),
		(anim->getPosition().y + hauteurJambe + hauteurBassin + hauteurTronc + rayonTete),
		(anim->getPosition().z + (largeurTronc/2)));
	tete.setAnim(animTete);
	tete.render();

	glPopMatrix();
	glPushMatrix();

}



///////////////////////////////////////////
///////////		PARALLELEPIPEDE	///////////
///////////////////////////////////////////
Parallelepipede::Parallelepipede(double len, double wid, double hei, Color co)
{
	length = len;
	width = wid;
	height = hei;
	col = co;
}

void Parallelepipede::update(double delta_t)
{
	// Do nothing, no physics associated toa table
	glColor3f(col.r, col.g, col.b);
}


void Parallelepipede::render()
{
	//glScaled(0.15, 0.15, 0.15);

	glEnable(GL_DEPTH_TEST);

	Vector3 p = anim->getPosition();


	glBegin(GL_QUADS);

	glColor3f(col.r, col.g, col.b); //face fond droit
	glVertex3d(p.x, p.y, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y + height, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x, p.y + height, p.z);

	glColor3f(col.r, col.g, col.b); //face  fond gauche
	glVertex3d(p.x, p.y, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x, p.y, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x, p.y + height, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x, p.y + height, p.z);

	glColor3f(col.r, col.g, col.b); //face du bas
	glVertex3d(p.x, p.y, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x, p.y, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y, p.z);


	glColor3f(col.r, col.g, col.b); //face avant droit
	glVertex3d(p.x + length, p.y, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y + height, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y + height, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y, p.z + width);

	glColor3f(col.r, col.g, col.b); //face avant gauche
	glVertex3d(p.x, p.y, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x, p.y + height, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y + height, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y, p.z + width);

	glColor3f(col.r, col.g, col.b); //face du haut
	glVertex3d(p.x, p.y + height, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x, p.y + height, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y + height, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y + height, p.z);

	glEnd();


	// contours
	// face haut

	glLineWidth(0.5);
	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINES);

	glVertex3d(p.x, p.y + height, p.z);
	glVertex3d(p.x, p.y + height, p.z + width);

	glVertex3d(p.x, p.y + height, p.z + width);
	glVertex3d(p.x + length, p.y + height, p.z + width);


	glVertex3d(p.x + length, p.y + height, p.z + width);
	glVertex3d(p.x + length, p.y + height, p.z);

	glVertex3d(p.x + length, p.y + height, p.z);
	glVertex3d(p.x, p.y + height, p.z);

	glVertex3d(p.x, p.y, p.z);
	glVertex3d(p.x, p.y + height, p.z);

	glVertex3d(p.x, p.y, p.z + width);
	glVertex3d(p.x, p.y + height, p.z + width);

	glVertex3d(p.x + length, p.y, p.z + width);
	glVertex3d(p.x + length, p.y + height, p.z + width);

	glVertex3d(p.x + length, p.y, p.z);
	glVertex3d(p.x + length, p.y + height, p.z);

	glVertex3d(p.x, p.y, p.z);
	glVertex3d(p.x, p.y, p.z + width);

	glVertex3d(p.x, p.y, p.z + width);
	glVertex3d(p.x + length, p.y, p.z + width);

	glVertex3d(p.x + length, p.y, p.z + width);
	glVertex3d(p.x + length, p.y, p.z);

	glVertex3d(p.x + length, p.y, p.z);
	glVertex3d(p.x, p.y, p.z);


	glEnd();

}







///////////////////////////////
////	MANCHE A AIR	///////
///////////////////////////////
MancheAAir::MancheAAir(Color co, Vector3 ve)
{
	vent = ve;
	col = co;
}
/*
void MancheAAir::setAngle(double aX, double aY, double aZ)
{
	angleX = aX * 360;
	angleY = aY * 360;
	angleZ = aZ * 360;
}*/


void MancheAAir::update(double delta_t)
{
	// Complete this part
}

void MancheAAir::render()
{
	double topRay = 0.15;
	double bottomRay = 0.05;
	double length = 0.8;


	// create cilynder
	GLUquadric* params;
	params = gluNewQuadric();

	// set possition
	glTranslated(anim->getPosition().x, anim->getPosition().y, anim->getPosition().z);


	/*
	Vector3 ventNormalise = vent.normalize();
	cout << 360.0 * ventNormalise << endl;
	*/


	// Get the angle of rotation of the cap
	/*
	double L = vent.norm();
	if ((vent.x != 0.0) || (vent.y != 0.0)) {
		glRotated(atan2(vent.y, vent.x) / RADPERDEG, 0.0, 0.0, 1.0);
		glRotated(atan2(sqrt(vent.x * vent.x + vent.y * vent.y), vent.z) / RADPERDEG, 0.0, 1.0, 0.0);
	}
	else if (vent.z < 0) {
		glRotated(180, 1.0, 0.0, 0.0);
	}
	*/

	

	// Degree = radian * 180/π
	// x
	glRotated((vent.x * 180/3.14), 1, 0, 0);
	// y
	glRotated((vent.y * 180 / 3.14) + 180, 0, 1, 0);
	// z
	glRotated((vent.z * 180 / 3.14), 0, 0, 1);
	

	glColor3f(col.r, col.g, col.b);

	gluQuadricDrawStyle(params, GLU_FLAT);

	gluCylinder(params, bottomRay, topRay, length, 20, 1);
	//gluCylinder(GLUquadric* params,base,top,height,slices,stacks);
	gluDeleteQuadric(params);


}
