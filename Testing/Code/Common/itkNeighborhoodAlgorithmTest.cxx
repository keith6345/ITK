 /*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit (ITK)
  Module:    itkNeighborhoodAlgorithmTest.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#include "itkImage.h"
#include "itkNeighborhood.h"
#include "itkRegionNeighborhoodIterator.h"
#include "itkImageRegionIterator.h"
#include "itkSmartRegionNeighborhoodIterator.h"
#include "itkRandomAccessNeighborhoodIterator.h"
#include "itkNeighborhoodAlgorithm.h"
#include "itkDerivativeOperator.h"
#include <iostream>

inline void println(char *s) { std::cout << s << std::endl; }

int main()
{
  typedef itk::Image<float, 2> ImageType2D;
  typedef itk::Image<float, 3> ImageType3D;
  typedef itk::Image<float, 4> ImageTypeND;

  println("Creating some images");
  
  // Create some images  
  itk::ImageRegion<2> Region2D;
  itk::ImageRegion<3> Region3D;
  itk::ImageRegion<4> RegionND;
  
  itk::Size<2>  size2D;
  size2D[0] = 123;
  size2D[1] = 241;

  itk::Size<3>  size3D;
  size3D[0] = 123;
  size3D[1] = 241;
  size3D[2] = 10;
  
  itk::Size<4>  sizeND;
  sizeND[0] = 100;
  sizeND[1] = 100;
  sizeND[2] = 4;
  sizeND[3] = 3;
  
  itk::Index<2> orig2D;
  orig2D[0] = 0;
  orig2D[1] = 0;

  itk::Index<3> orig3D;
  orig3D[0] = 0;
  orig3D[1] = 0;
  orig3D[2] = 0;
  
  itk::Index<4> origND;
  origND[0] = 0;
  origND[1] = 0;
  origND[2] = 0;
  origND[3] = 0;
  
  Region2D.SetSize(size2D);
  Region3D.SetSize(size3D);
  RegionND.SetSize(sizeND);
  
  Region2D.SetIndex(orig2D);
  Region3D.SetIndex(orig3D);
  RegionND.SetIndex(origND);

  ImageType2D::Pointer image2D = ImageType2D::New();
  ImageType3D::Pointer image3D = ImageType3D::New();
  ImageTypeND::Pointer imageND = ImageTypeND::New();

  image2D->SetLargestPossibleRegion(Region2D);
  image3D->SetLargestPossibleRegion(Region3D);
  imageND->SetLargestPossibleRegion(RegionND);

  image2D->SetBufferedRegion(Region2D);
  image3D->SetBufferedRegion(Region3D);
  imageND->SetBufferedRegion(RegionND);

  image2D->SetRequestedRegion(Region2D);
  image3D->SetRequestedRegion(Region3D);
  imageND->SetRequestedRegion(RegionND);

  image2D->Allocate();
  image3D->Allocate();
  imageND->Allocate();

  itk::ImageRegionIterator<ImageType2D> it2D(image2D,
                                          image2D->GetRequestedRegion());
  itk::ImageRegionIterator<ImageType3D> it3D(image3D,
                                          image3D->GetRequestedRegion());
  itk::ImageRegionIterator<ImageTypeND> itND(imageND,
                                          imageND->GetRequestedRegion());

  println("Initializing some images");
  
  for (it2D = it2D.Begin(); it2D != it2D.End(); ++it2D) it2D.Set( 1.0f );
  for (it3D = it3D.Begin(); it3D != it3D.End(); ++it3D) it3D.Set( 1.0f );
  for (itND = itND.Begin(); itND != itND.End(); ++itND) itND.Set( 1.0f );

  // Set up some neighborhood iterators
  println("Setting up some neighborhood iterators");
  itk::Offset<2> orig2Dm;
  orig2Dm[0] = 55;
  orig2Dm[1] = 55;
  
  itk::Offset<3> orig3Dm;
  orig3Dm[0] = 55;
  orig3Dm[1] = 55;
  orig3Dm[2] = 5;
  
  itk::Offset<4> origNDm;
  origNDm[0] = 1;
  origNDm[1] = 3;
  origNDm[2] = 1;
  origNDm[3] = 1;

  itk::Size<2> sz2;
  sz2[0] = 2;
  sz2[1] = 3;
  
  itk::Size<3> sz3;
  sz3[0] = 2;
  sz3[1] = 3;
  sz3[2] = 1;
  
  itk::Size<4> szN;
  szN[0] = 1;
  szN[1] = 3;
  szN[2] = 1;
  szN[3] = 1;

  itk::RegionNeighborhoodIterator<ImageType2D> rni2D(sz2, image2D,
                                           image2D->GetRequestedRegion());
  itk::RandomAccessNeighborhoodIterator<ImageType3D> rni3D(sz3, image3D,
                                           image3D->GetRequestedRegion());
  itk::RandomAccessNeighborhoodIterator<ImageTypeND> rniND(szN, imageND,
                                           imageND->GetRequestedRegion());

  rniND.Print(std::cout);

  println("Grabbing some neighborhoods");
  itk::Neighborhood<float, 2> n2 = rni2D.GetNeighborhood();
  rni3D += orig3Dm;
  itk::Neighborhood<float, 3> n3 = rni3D.GetNeighborhood();
  std::cout << imageND << std::endl;
  rniND += origNDm;
  rniND.Print(std::cout);
  std::cout << rniND.Center() << std::endl;
  itk::Neighborhood<float, 4> nN = rniND.GetNeighborhood();
  nN.Print(std::cout);

  // Test inner product
  println("Testing inner product variations");
  itk::DerivativeOperator<float, 2> d2D;
  itk::DerivativeOperator<float, 3> d3D;
  itk::DerivativeOperator<float, 4> dND;

  d2D.SetDirection(0);
  d3D.SetDirection(0);
  dND.SetDirection(0);
  
  d2D.SetOrder(1);
  d3D.SetOrder(1);
  dND.SetOrder(1);

  d2D.CreateDirectional();
  d3D.CreateDirectional();
  dND.CreateDirectional();
  
  itk::SmartRegionNeighborhoodIterator<ImageType2D>
    rni2Dd(d2D.GetRadius(), image2D, image2D->GetRequestedRegion());
  itk::SmartRegionNeighborhoodIterator<ImageType3D>
    rni3Dd(d3D.GetRadius(), image3D, image3D->GetRequestedRegion());
  itk::SmartRegionNeighborhoodIterator<ImageTypeND>
    rniNDd(dND.GetRadius(), imageND, imageND->GetRequestedRegion());

  println("A");
  itk::NeighborhoodAlgorithm
    ::IteratorInnerProduct<itk::NeighborhoodIterator<ImageType2D>,
    itk::Neighborhood<float, 2> > ipi2D;
  ipi2D(rni2Dd, d2D);

  println("B");
  itk::NeighborhoodAlgorithm
    ::InnerProduct<itk::Neighborhood<float, 2>, itk::Neighborhood<float,2> >
    ipn2D;
  n2 = rni2Dd.GetNeighborhood();
  ipn2D(n2, d2D);

  println("C");
  itk::NeighborhoodAlgorithm
    ::IteratorInnerProduct<itk::NeighborhoodIterator<ImageType3D>,
    itk::Neighborhood<float, 3> > ipi3D;
  ipi3D(rni3Dd, d3D);

  println("D");
  itk::NeighborhoodAlgorithm
    ::InnerProduct<itk::Neighborhood<float, 3>,
    itk::Neighborhood<float, 3> > ipn3D;
  n3 = rni3Dd.GetNeighborhood();
  ipn3D(n3, d3D);

  println("E");
  itk::NeighborhoodAlgorithm
    ::IteratorInnerProduct<itk::NeighborhoodIterator<ImageTypeND>,
    itk::Neighborhood<float, 4> > ipiND;
  ipiND(rniNDd, dND);

  println("F");
  itk::NeighborhoodAlgorithm
    ::InnerProduct<itk::Neighborhood<float, 4>,
    itk::Neighborhood<float, 4> > ipnND;
  nN = rniNDd.GetNeighborhood();
  ipnND(nN, dND);
  
  println("G");
  itk::NeighborhoodAlgorithm
    ::BoundsCheckingIteratorInnerProduct<itk::
    SmartRegionNeighborhoodIterator<ImageTypeND>,
    itk::Neighborhood<float, 4> > ipibND;
  ipibND(rniNDd, dND);

  return 0;
}
