#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <QDesktopServices>
#include <QProcess>

namespace Ui {
class MainWindow;
}

using namespace OpenMesh;
using namespace OpenMesh::Attributes;

struct MyTraits : public OpenMesh::DefaultTraits
{
    // use vertex normals and vertex colors
    VertexAttributes( OpenMesh::Attributes::Normal | OpenMesh::Attributes::Color | OpenMesh::Attributes::Status);
    // store the previous halfedge
    HalfedgeAttributes( OpenMesh::Attributes::PrevHalfedge );
    // use face normals face colors
    FaceAttributes( OpenMesh::Attributes::Normal | OpenMesh::Attributes::Color | OpenMesh::Attributes::Status);
    EdgeAttributes( OpenMesh::Attributes::Color | OpenMesh::Attributes::Status );
    // vertex thickness
    VertexTraits{float thickness; float value;};
    // edge thickness
    EdgeTraits{float thickness;};
};
typedef OpenMesh::TriMesh_ArrayKernelT<MyTraits> MyMesh;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void displayMesh(MyMesh *_mesh, bool isTemperatureMap = false, float mapRange = -1);
    void resetAllColorsAndThickness(MyMesh* _mesh);
    MyMesh * cut(MyMesh * _mesh, MyMesh::Point P1, MyMesh::Point P2, MyMesh::Point P3);
    float * equation_plane(MyMesh::Point P1
                        , MyMesh::Point P2
                        , MyMesh::Point P3);
    void showBorder(MyMesh* _mesh,float * eq_plane) ;
    //void changeValuePointCut(OpenMesh::Vec3f first, OpenMesh::Vec3f last);
public slots:
    void changeValuePointCut(OpenMesh::Vec3f first, OpenMesh::Vec3f last);
private slots:
    void on_pushButton_chargement_clicked();

    void on_pushButton_generer_clicked();

    void on_pushButton_couper_clicked();

private:

    MyMesh mesh;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
