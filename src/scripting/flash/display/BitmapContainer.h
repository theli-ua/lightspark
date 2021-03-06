/**************************************************************************
    Lightspark, a free flash player implementation

    Copyright (C) 2012-2013  Alessandro Pignotti (a.pignotti@sssup.it)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#ifndef SCRIPTING_FLASH_DISPLAY_BITMAPCONTAINER_H
#define SCRIPTING_FLASH_DISPLAY_BITMAPCONTAINER_H 1

#include "compat.h"
#include "memory_support.h"
#include "smartrefs.h"
#include <vector>

namespace lightspark
{

class BitmapContainer : public RefCountable
{
protected:
	size_t stride;
	size_t dataSize;
	int32_t width;
	int32_t height;
	uint32_t *getDataNoBoundsChecking(int32_t x, int32_t y);
public:
	BitmapContainer(MemoryAccount* m);
	std::vector<uint8_t, reporter_allocator<uint8_t>> data;
	uint8_t* getData() { return &data[0]; }
	const uint8_t* getData() const { return &data[0]; }
	enum BITMAP_FORMAT { RGB15, RGB24, ARGB32 };
	bool fromRGB(uint8_t* rgb, uint32_t width, uint32_t height, BITMAP_FORMAT format);
	bool fromJPEG(uint8_t* data, int len, const uint8_t *tablesData=NULL, int tablesLen=0);
	bool fromJPEG(std::istream& s);
	bool fromPNG(std::istream& s);
	bool fromPalette(uint8_t* inData, uint32_t width, uint32_t height, uint32_t inStride, uint8_t* palette, unsigned numColors, unsigned paletteBPP);
	void setAlpha(int32_t x, int32_t y, uint8_t alpha);
	void setPixel(int32_t x, int32_t y, uint32_t color, bool setAlpha);
	uint32_t getPixel(int32_t x, int32_t y);
	void copyRectangle(_R<BitmapContainer> source, int32_t sourceLeft,
			   int32_t sourceTop, int32_t destLeft, int32_t destTop,
			   int32_t width, int32_t height, bool mergeAlpha);
	void fillRectangle(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t color, bool useAlpha);
	bool scroll(int32_t x, int32_t y);
	void floodFill(int32_t x, int32_t y, uint32_t color);
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	bool isEmpty() const { return data.empty(); }
	void clear();
};

};
#endif /* SCRIPTING_FLASH_DISPLAY_BITMAPCONTAINER_H */
