// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXTENSION_BENJAMIN_HAMPE_AT_GMX_DE_H__
#define __IRR_EXTENSION_BENJAMIN_HAMPE_AT_GMX_DE_H__

#include <irrlicht.h>

#include "audio/CRectangleOscillator.h"
#include "audio/CSawOscillator.h"
#include "audio/CSineOscillator.h"
#include "audio/CTriangleOscillator.h"
#include "audio/FourierTransformRtoC.h"

#include "core/IFunction.h"
#include "core/IStringable.h"
#include "core/CDateTime.h"
#include "core/CMath.h"
#include "core/CMatrix.h"
#include "core/E_ENUMERATION_STRINGS.h"
#include "core/irrUString.h"
#include "core/sinCosTable.h"
#include "core/sprintf.h"

#include "gui/CGUIImageViewer.h"
//#include "gui/CGUIPlot.h"
#include "gui/CGUITTFont.h"
#include "gui/IGUITTFont.h"

#include "io/CXMLWriterUTF8.h"
#include "io/FileSystem.h"
#include "io/readFile.h"
#include "io/svgLib.h"

#include "scene/CAutoMeshSceneNode.h"
#include "scene/CMatrixSceneNode.h"
#include "scene/geometry.h"

#include "video/CLinearColorGradient.h"
#include "video/ColorConstants.h"
#include "video/drawCircle.h"
#include "video/drawEllipse.h"
#include "video/drawGrid.h"
#include "video/drawImage.h"
#include "video/drawLine.h"
#include "video/drawLoadingScreen.h"
#include "video/drawPixel.h"
#include "video/drawPolyLine.h"
#include "video/drawRect.h"
#include "video/drawRoundRect.h"
#include "video/drawText.h"
#include "video/IColorGradient.h"
#include "video/imageAtlas.h"
#include "video/imageBlend.h"
#include "video/imageFilter.h"
#include "video/imageFloodFill.h"
#include "video/imageRepeat.h"
#include "video/imageResize.h"
#include "video/imageScale.h"
#include "video/renderByPrimitiveType.h"
#include "video/renderToImage.h"

#endif // __IRR_EXTENSION_BENJAMIN_HAMPE_AT_GMX_DE_H__
