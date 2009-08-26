// ***************************************************************************
//
// Copyright (c) 2000 - 2009, Lawrence Livermore National Security, LLC
// Produced at the Lawrence Livermore National Laboratory
// LLNL-CODE-400124
// All rights reserved.
//
// This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
// full copyright notice is contained in the file COPYRIGHT located at the root
// of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
//
// Redistribution  and  use  in  source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
//  - Redistributions of  source code must  retain the above  copyright notice,
//    this list of conditions and the disclaimer below.
//  - Redistributions in binary form must reproduce the above copyright notice,
//    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
//    documentation and/or other materials provided with the distribution.
//  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
//    be used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
// ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
// LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
// DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
// SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
// CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
// LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
// OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ***************************************************************************

package llnl.visit;


// ****************************************************************************
// Class: InteractorAttributes
//
// Purpose:
//    This class contains attributes associated with the main window.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class InteractorAttributes extends AttributeSubject
{
    private static int numAdditionalAttributes = 5;

    // Enum values
    public final static int NAVIGATIONMODE_TRACKBALL = 0;
    public final static int NAVIGATIONMODE_DOLLY = 1;
    public final static int NAVIGATIONMODE_FLYTHROUGH = 2;


    public InteractorAttributes()
    {
        super(numAdditionalAttributes);

        showGuidelines = true;
        clampSquare = false;
        fillViewportOnZoom = true;
        navigationMode = NAVIGATIONMODE_TRACKBALL;
        axisArraySnap = true;
    }

    public InteractorAttributes(int nMoreFields)
    {
        super(numAdditionalAttributes + nMoreFields);

        showGuidelines = true;
        clampSquare = false;
        fillViewportOnZoom = true;
        navigationMode = NAVIGATIONMODE_TRACKBALL;
        axisArraySnap = true;
    }

    public InteractorAttributes(InteractorAttributes obj)
    {
        super(numAdditionalAttributes);

        showGuidelines = obj.showGuidelines;
        clampSquare = obj.clampSquare;
        fillViewportOnZoom = obj.fillViewportOnZoom;
        navigationMode = obj.navigationMode;
        axisArraySnap = obj.axisArraySnap;

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return numAdditionalAttributes;
    }

    public boolean equals(InteractorAttributes obj)
    {
        // Create the return value
        return ((showGuidelines == obj.showGuidelines) &&
                (clampSquare == obj.clampSquare) &&
                (fillViewportOnZoom == obj.fillViewportOnZoom) &&
                (navigationMode == obj.navigationMode) &&
                (axisArraySnap == obj.axisArraySnap));
    }

    // Property setting methods
    public void SetShowGuidelines(boolean showGuidelines_)
    {
        showGuidelines = showGuidelines_;
        Select(0);
    }

    public void SetClampSquare(boolean clampSquare_)
    {
        clampSquare = clampSquare_;
        Select(1);
    }

    public void SetFillViewportOnZoom(boolean fillViewportOnZoom_)
    {
        fillViewportOnZoom = fillViewportOnZoom_;
        Select(2);
    }

    public void SetNavigationMode(int navigationMode_)
    {
        navigationMode = navigationMode_;
        Select(3);
    }

    public void SetAxisArraySnap(boolean axisArraySnap_)
    {
        axisArraySnap = axisArraySnap_;
        Select(4);
    }

    // Property getting methods
    public boolean GetShowGuidelines() { return showGuidelines; }
    public boolean GetClampSquare() { return clampSquare; }
    public boolean GetFillViewportOnZoom() { return fillViewportOnZoom; }
    public int     GetNavigationMode() { return navigationMode; }
    public boolean GetAxisArraySnap() { return axisArraySnap; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteBool(showGuidelines);
        if(WriteSelect(1, buf))
            buf.WriteBool(clampSquare);
        if(WriteSelect(2, buf))
            buf.WriteBool(fillViewportOnZoom);
        if(WriteSelect(3, buf))
            buf.WriteInt(navigationMode);
        if(WriteSelect(4, buf))
            buf.WriteBool(axisArraySnap);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetShowGuidelines(buf.ReadBool());
            break;
        case 1:
            SetClampSquare(buf.ReadBool());
            break;
        case 2:
            SetFillViewportOnZoom(buf.ReadBool());
            break;
        case 3:
            SetNavigationMode(buf.ReadInt());
            break;
        case 4:
            SetAxisArraySnap(buf.ReadBool());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + boolToString("showGuidelines", showGuidelines, indent) + "\n";
        str = str + boolToString("clampSquare", clampSquare, indent) + "\n";
        str = str + boolToString("fillViewportOnZoom", fillViewportOnZoom, indent) + "\n";
        str = str + indent + "navigationMode = ";
        if(navigationMode == NAVIGATIONMODE_TRACKBALL)
            str = str + "NAVIGATIONMODE_TRACKBALL";
        if(navigationMode == NAVIGATIONMODE_DOLLY)
            str = str + "NAVIGATIONMODE_DOLLY";
        if(navigationMode == NAVIGATIONMODE_FLYTHROUGH)
            str = str + "NAVIGATIONMODE_FLYTHROUGH";
        str = str + "\n";
        str = str + boolToString("axisArraySnap", axisArraySnap, indent) + "\n";
        return str;
    }


    // Attributes
    private boolean showGuidelines;
    private boolean clampSquare;
    private boolean fillViewportOnZoom;
    private int     navigationMode;
    private boolean axisArraySnap;
}

