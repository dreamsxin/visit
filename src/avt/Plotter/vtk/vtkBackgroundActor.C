// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include "vtkBackgroundActor.h"

#include <vtkCellArray.h>
#include <vtkMath.h>
#include <vtkMatrix4x4.h>
#include <vtkObjectFactory.h>
#include <vtkPointData.h>
#include <vtkViewport.h>


// ***************************************************************************
//  Modifications:
//
//    Kathleen Bonnell, Wed Mar  6 13:48:48 PST 2002
//    Use new vtk macro in place of New method. 
// ***************************************************************************

vtkStandardNewMacro(vtkBackgroundActor);


vtkBackgroundActor::vtkBackgroundActor()
{
    this->GradientFillMode = 0;
    this->NumRings = 4;
    this->NumRadialSteps = 20;

    this->GradientActor = NULL;
    this->GradientMapper = NULL;
    this->GradientData = NULL;

    this->GradientCoords[0] = -1.;
    this->GradientCoords[1] = -1.;
    this->GradientCoords[2] = -1.;
    this->GradientCoords[3] = -1.;

    this->GradientColors[0][0] = 0.;
    this->GradientColors[0][1] = 1.;
    this->GradientColors[0][2] = 1.;

    this->GradientColors[1][0] = 0.;
    this->GradientColors[1][1] = 1.;
    this->GradientColors[1][2] = 1.;

    this->GradientColors[2][0] = 0.;
    this->GradientColors[2][1] = 0.;
    this->GradientColors[2][2] = 1.;

    this->GradientColors[3][0] = 0.;
    this->GradientColors[3][1] = 0.;
    this->GradientColors[3][2] = 1.;
}


vtkBackgroundActor::~vtkBackgroundActor()
{
    DestroyBackground();
}

void
vtkBackgroundActor::DestroyBackground()
{
    if(this->GradientActor != NULL)
    {
        this->GradientActor->Delete();
        this->GradientActor = NULL;
    }

    if(this->GradientMapper != NULL)
    {
        this->GradientMapper->Delete();
        this->GradientMapper = NULL;
    }

    if(this->GradientData != NULL)
    {
        this->GradientData->Delete();
        this->GradientData = NULL;
    }
}

// ***************************************************************************
//  Modifications:
//
//    Kathleen Bonnell, Mon Oct 29 14:21:59 PST 2001 
//    Made ptIds of type vtkIdType to match VTK 4.0 API.
//
//    Kathleen Bonnell, Fri Feb  8 11:03:49 PST 2002
//    vtkScalars has been deprecated in VTK 4.0, use vtkUnsignedCharArray
//    for colors instead.
// ***************************************************************************

void
vtkBackgroundActor::CreateBackground()
{
    this->GradientData = vtkPolyData::New();

    if(this->GradientFillMode < 4)
    {
        int numPts = 4;
        vtkPoints *pts = vtkPoints::New();
        pts->SetNumberOfPoints(numPts);
        vtkCellArray *polys = vtkCellArray::New();
        polys->Allocate(polys->EstimateSize(numPts * 3,4)); 
        vtkUnsignedCharArray *colors = vtkUnsignedCharArray::New();
        colors->SetNumberOfComponents(3);
        colors->SetNumberOfTuples(numPts);

        // Store the colors and points in the polydata.
        this->GradientData->Initialize();
        this->GradientData->SetPoints(pts);
        this->GradientData->SetPolys(polys);
        this->GradientData->GetPointData()->SetScalars(colors);
        pts->Delete(); polys->Delete(); colors->Delete(); 

        // Add points to the vertex list.
        double coord[3];
        coord[2] = 0.0;
        coord[0] = this->GradientCoords[0];
        coord[1] = this->GradientCoords[1];
        pts->SetPoint(0, coord);
        coord[0] = this->GradientCoords[2];
        coord[1] = this->GradientCoords[1];
        pts->SetPoint(1, coord);
        coord[0] = this->GradientCoords[2];
        coord[1] = this->GradientCoords[3];
        pts->SetPoint(2, coord);
        coord[0] = this->GradientCoords[0];
        coord[1] = this->GradientCoords[3];
        pts->SetPoint(3, coord);

        // Add a cell to the polydata.
        vtkIdType ptIds[4];
        ptIds[0] = 0;
        ptIds[1] = 1;
        ptIds[2] = 2;
        ptIds[3] = 3;
        polys->InsertNextCell(4, ptIds);

        // Write the colors into the array directly
        unsigned char *rgb = colors->GetPointer(0);
        rgb[0] = (unsigned char)((float)this->GradientColors[0][0] * 255.f);
        rgb[1] = (unsigned char)((float)this->GradientColors[0][1] * 255.f);
        rgb[2] = (unsigned char)((float)this->GradientColors[0][2] * 255.f);
        rgb = colors->GetPointer(3);
        rgb[0] = (unsigned char)((float)this->GradientColors[1][0] * 255.f);
        rgb[1] = (unsigned char)((float)this->GradientColors[1][1] * 255.f);
        rgb[2] = (unsigned char)((float)this->GradientColors[1][2] * 255.f);
        rgb = colors->GetPointer(6);
        rgb[0] = (unsigned char)((float)this->GradientColors[2][0] * 255.f);
        rgb[1] = (unsigned char)((float)this->GradientColors[2][1] * 255.f);
        rgb[2] = (unsigned char)((float)this->GradientColors[2][2] * 255.f);
        rgb = colors->GetPointer(9);
        rgb[0] = (unsigned char)((float)this->GradientColors[3][0] * 255.f);
        rgb[1] = (unsigned char)((float)this->GradientColors[3][1] * 255.f);
        rgb[2] = (unsigned char)((float)this->GradientColors[3][2] * 255.f);
    }
    else
    {
        int numPts = 1 + this->NumRings * this->NumRadialSteps;
        vtkPoints *pts = vtkPoints::New();
        pts->SetNumberOfPoints(numPts);
        vtkCellArray *polys = vtkCellArray::New();
        polys->Allocate(polys->EstimateSize(numPts * 3,4)); 
        vtkUnsignedCharArray *colors = vtkUnsignedCharArray::New();
        colors->SetNumberOfComponents(3);
        colors->SetNumberOfTuples(numPts);

        // Store the colors and points in the polydata.
        this->GradientData->Initialize();
        this->GradientData->SetPoints(pts);
        this->GradientData->SetPolys(polys);
        this->GradientData->GetPointData()->SetScalars(colors);
        pts->Delete(); polys->Delete(); colors->Delete(); 

        double CenterX = (this->GradientCoords[0] + this->GradientCoords[2]) * 0.5;
        double CenterY = (this->GradientCoords[1] + this->GradientCoords[3]) * 0.5;
        double dX = CenterX - this->GradientCoords[0];
        double dY = CenterY - this->GradientCoords[1];
        double Radius = sqrt(dX*dX + dY*dY) * 1.02;
        double dTheta = 2 * 3.14159 / double(this->NumRadialSteps);

        // Add the first point and its color.
        double coord[3];
        coord[2] = 0.0;
        coord[0] = CenterX;
        coord[1] = CenterY;
        pts->SetPoint(0, coord);
        unsigned char *rgb = colors->GetPointer(0);
        rgb[0] = (unsigned char)((float)this->GradientColors[0][0] * 255.f);
        rgb[1] = (unsigned char)((float)this->GradientColors[0][1] * 255.f);
        rgb[2] = (unsigned char)((float)this->GradientColors[0][2] * 255.f);

        // Add the radial cells to the polydata.
        int ptIndex = 1;
        for(int ring = 0; ring < this->NumRings; ++ring)
        {
            double t = (double(ring + 1) / double(this->NumRings));
            double RingRadius = Radius * t;
            double theta = 0.;

            // Figure the color for the points at this level of the ring.
            double cR = (1 - t) * this->GradientColors[0][0] +
                       t * this->GradientColors[1][0];
            double cG = (1 - t) * this->GradientColors[0][1] +
                       t * this->GradientColors[1][1];
            double cB = (1 - t) * this->GradientColors[0][2] +
                       t * this->GradientColors[1][2];

            for(int i = 0; i < this->NumRadialSteps; ++i, theta += dTheta)
            {
                // Create the coordinate.
                coord[0] = cos(theta) * RingRadius + CenterX;
                coord[1] = sin(theta) * RingRadius + CenterY;
                pts->SetPoint(ptIndex, coord);

                // Add the color.
                rgb = colors->GetPointer(ptIndex * 3);
                rgb[0] = (unsigned char)((float)cR * 255.f);
                rgb[1] = (unsigned char)((float)cG * 255.f);
                rgb[2] = (unsigned char)((float)cB * 255.f);
                ++ptIndex;

                // Add the cell to the polydata.
                vtkIdType ptIds[4];
                if(ring == 0)
                {
                    ptIds[0] = 0;
                    ptIds[1] = i + 1;
                    ptIds[2] = ((i + 1) < this->NumRadialSteps) ? (i + 2) : 1;
                    polys->InsertNextCell(3, ptIds);
                }
                else
                {
                    ptIds[0] = i + ((ring - 1) * this->NumRadialSteps) + 1;
                    ptIds[1] = i + (ring * this->NumRadialSteps) + 1;
                    ptIds[2] = ((i + 1) < this->NumRadialSteps) ? (ptIds[1] + 1) :
                        (ptIds[1] - this->NumRadialSteps + 1);
                    ptIds[3] = ((i + 1) < this->NumRadialSteps) ? (ptIds[0] + 1) :
                        (ptIds[0] - this->NumRadialSteps + 1);
                    polys->InsertNextCell(4, ptIds);
                }
            }
        }
    }

    this->GradientMapper = vtkPolyDataMapper2D::New();
    this->GradientMapper->SetInputData(this->GradientData);

    this->GradientActor = vtkActor2D::New();
//    this->GradientActor->Modified();
    this->GradientActor->SetMapper(this->GradientMapper);
}


int vtkBackgroundActor::RenderOverlay(vtkViewport *viewport)
{
    // Get the normalized device coordinates in device coordinates.
    double newPts[4];
    newPts[0] = 0.;
    newPts[1] = 0.;
    newPts[2] = 1.;
    newPts[3] = 1.;
    viewport->NormalizedDisplayToDisplay(newPts[0], newPts[1]);
    viewport->NormalizedDisplayToDisplay(newPts[2], newPts[3]);

    // See if the device coordinates do not match the stored device coords.
    bool sizeChanged = (newPts[0] != this->GradientCoords[0]) ||
                       (newPts[1] != this->GradientCoords[1]) ||
                       (newPts[2] != this->GradientCoords[2]) ||
                       (newPts[3] != this->GradientCoords[3]);

    // See if this actor's modification time is greater than that of the
    // internal 2d actor.
    bool stateChanged = false;
    if(this->GradientActor != NULL)
        stateChanged = this->GetMTime() > this->GradientActor->GetMTime();

    // Redo the gradient background
    if(sizeChanged || stateChanged || GradientData == NULL ||
       GradientActor == NULL || GradientMapper == NULL)
    {
        this->GradientCoords[0] = newPts[0];
        this->GradientCoords[1] = newPts[1];
        this->GradientCoords[2] = newPts[2];
        this->GradientCoords[3] = newPts[3];

        DestroyBackground();
        CreateBackground();
    }

    // Render the gradient actor.
    int retval = this->GradientActor->RenderOverlay(viewport);

    return retval;
}


int vtkBackgroundActor::RenderOpaqueGeometry(vtkViewport *viewport)
{
    return 0;
}

void vtkBackgroundActor::SetColors(const double colors[4][3])
{
    this->GradientColors[0][0] = colors[0][0];
    this->GradientColors[0][1] = colors[0][1];
    this->GradientColors[0][2] = colors[0][2];

    this->GradientColors[1][0] = colors[1][0];
    this->GradientColors[1][1] = colors[1][1];
    this->GradientColors[1][2] = colors[1][2];

    this->GradientColors[2][0] = colors[2][0];
    this->GradientColors[2][1] = colors[2][1];
    this->GradientColors[2][2] = colors[2][2];

    this->GradientColors[3][0] = colors[3][0];
    this->GradientColors[3][1] = colors[3][1];
    this->GradientColors[3][2] = colors[3][2];
    this->Modified();
}

void vtkBackgroundActor::SetColor(int id, const double color[3])
{
    if(id < 0 || id > 3)
        return;

    this->GradientColors[id][0] = color[0];
    this->GradientColors[id][1] = color[1];
    this->GradientColors[id][2] = color[2];
    this->Modified();
}

void vtkBackgroundActor::SetGradientFillMode(int mode)
{
    this->GradientFillMode = mode;
    this->Modified();
}

void vtkBackgroundActor::SetNumRings(int rings)
{
    this->NumRings = rings;
    this->Modified();
}

void vtkBackgroundActor::SetNumRadialSteps(int steps)
{
    this->NumRadialSteps = steps;
    this->Modified();
}

// ***************************************************************************
//  Modifications:
//
//    Kathleen Bonnell, Wed Mar  6 13:48:48 PST 2002
//    Call superclass's method the new vtk way. 
// ***************************************************************************

void vtkBackgroundActor::PrintSelf(ostream& os, vtkIndent indent)
{
    this->Superclass::PrintSelf(os, indent);

    os << indent << "GradientFillMode: " << this->GradientFillMode << endl;
    os << indent << "NumRings: " << this->NumRings << endl;
    os << indent << "NumRadialSteps: " << this->NumRadialSteps << endl;
    os << indent << "GradientColors: {"
       << "(" << this->GradientColors[0][0] << ","
       << this->GradientColors[0][1] << ","
       << this->GradientColors[0][2] << "), "
       << "(" << this->GradientColors[1][0] << ","
       << this->GradientColors[1][1] << ","
       << this->GradientColors[1][2] << "), "
       << "(" << this->GradientColors[2][0] << ","
       << this->GradientColors[2][1] << ","
       << this->GradientColors[2][2] << "), "
       << "(" << this->GradientColors[3][0] << ","
       << this->GradientColors[3][1] << ","
       << this->GradientColors[3][2] << ")}" << endl;
}

