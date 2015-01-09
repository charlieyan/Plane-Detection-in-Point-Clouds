#ifndef PLANE_H
#define PLANE_H

#include "Point.h"
#include <vector>
#include <iostream>
#include "RGB.h"
#include "UnionFind.h"

class Plane
{
public:
    //Plane(double a_, double b_, double c_, double d_) : a(a_), b(b_), c(c_), d(d_) {}
    Plane();
    // Plan passant par n points par minimisation des moindres carres
    Plane(const std::vector<SharedPoint>& pts);

    // Carre de la distance entre le point et le plan
    double distance(SharedPoint p);

    // Verifie si un point est acceptable dans le plan
    bool accept(SharedPoint p);

    // Si le plan est bien defini (vecteur normal non nul)
    bool isValid() {return a != 0 || b != 0 || c != 0;}

    // Ajoute un point au plan (sans recalculer l'equation)
    void addPoint(SharedPoint p, UnionFind<SharedPoint, RGB>& colors);

    // Calcule l'equation par minimisation des moindres carres.
    void computeEquation();

    // Lie un plan à ses points, calcule au passage le barycentre et le rayon du nuage de points
    void setPoints(const std::vector<SharedPoint>& pts);

    // Change la couleur des points du plan
    void setColor(RGB color, UnionFind<SharedPoint, RGB>& colors);

    // Decide si deux plans peuvent être fusionnes
    // dTheta est donne en radians.
    bool mergeableWith(const Plane& p, double dCos, double dL) const;

    // Inclut le plan p dans le plan objet, le plan p est vide.
    void merge(Plane& p, UnionFind<SharedPoint, RGB>& colors);

    // Donne la distance entre deux points selon la normale au plan
    double distanceAlong(Vec3 u, Vec3 v) const;

    // Valeur absolue du cosinus entre les vecteurs normaux.
    static double getCos(const Plane& p, const Plane& q);

private:
    // Initialise la matrice M
    void init();
    // Ajoute un point au plan (sans recalculer l'equation)
    void addPoint(const Point& p);

    //Coordinates corresponding to the plane equation ax+by+cz+d=0
    double a, b, c, d;

    // Matrix to compute the optimal equation given the points
    std::array<std::array<double, 4>, 3> m;
    // One point related to the plane
    SharedPoint point;
    // Number of points
    unsigned int count;

    //Attributes for plane merging
    Vec3 center; // Currently the barycenter, but it would be better to have the circumcenter if we could find an efficient computation method
    double radius;
    double thickness;

    friend std::ostream& operator<<(std::ostream& os, const Plane& p);
};

typedef std::shared_ptr<Plane> SharedPlane;

#endif // PLANE_H
