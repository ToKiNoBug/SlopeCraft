/*
 Copyright © 2021-2022  TokiNoBug
This file is part of SlopeCraft.

    SlopeCraft is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SlopeCraft is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SlopeCraft.  If not, see <https://www.gnu.org/licenses/>.

    Contact with me:
    github:https://github.com/ToKiNoBug
    bilibili:https://space.bilibili.com/351429231
*/

#ifndef KERNEL_H
#define KERNEL_H


#include "SlopeCraftL_global.h"
#define SCL_EXPORT SLOPECRAFTL_EXPORT

//#define SLOPECRAFTL_CAPI

namespace SlopeCraft {
#ifdef SLOPECRAFTL_CAPI
struct AbstractBlock;
#else
class AbstractBlock;
#endif
}   //  namespace SlopeCraft

#ifdef SLOPECRAFTL_CAPI
extern "C" {
namespace SlopeCraft{
AbstractBlock * SCL_EXPORT createBlock();
unsigned long long SCL_EXPORT blockSize(const AbstractBlock *);

///id of this block
const char* SCL_EXPORT getId(const AbstractBlock *);

///first version
unsigned char SCL_EXPORT getVersion(const AbstractBlock *);
///id in 1.12
const char* SCL_EXPORT getIdOld(const AbstractBlock *);
///if this block needs a glass block under it
bool SCL_EXPORT getNeedGlass(const AbstractBlock *);
///if this block emits light
bool SCL_EXPORT getDoGlow(const AbstractBlock *);
///if this block can be stolen by enderman
bool SCL_EXPORT getEndermanPickable(const AbstractBlock *);
///if this block can be burnt
bool SCL_EXPORT getBurnable(const AbstractBlock *);
///if this block can be used in wall-map
bool SCL_EXPORT getWallUseable(const AbstractBlock *);

///set block id
void SCL_EXPORT setId(AbstractBlock *,const char*);
///set first version
void SCL_EXPORT setVersion(AbstractBlock *,unsigned char);
///set id in 1.12
void SCL_EXPORT setIdOld(AbstractBlock *,const char*);
///set if this block needs a glass block under it
void SCL_EXPORT setNeedGlass(AbstractBlock *,bool);
///set if this block emits light
void SCL_EXPORT setDoGlow(AbstractBlock *,bool);
///set if this block can be stolen by enderman
void SCL_EXPORT setEndermanPickable(AbstractBlock *,bool);
///set if this block can be burnt
void SCL_EXPORT setBurnable(AbstractBlock *,bool);
///set if this block can be used in wall-map
void SCL_EXPORT setWallUseable(AbstractBlock *,bool);
///let *b equal to *this
void SCL_EXPORT copyTo(AbstractBlock *,AbstractBlock * b) ;
///set this block to air
void SCL_EXPORT clear(AbstractBlock *);
///replacement for operator delete
void SCL_EXPORT destroyBlock(AbstractBlock *);
}   //  namespace SlopeCraft
}   //  extern C
#endif  //  #ifdef SLOPECRAFTL_CAPI


#ifndef SLOPECRAFTL_CAPI
namespace SlopeCraft {
class SCL_EXPORT AbstractBlock
{
public:
    AbstractBlock();
    //virtual ~AbstractBlock() {};
    ///create a block
    static AbstractBlock * create();
    ///real size of this block
    virtual unsigned long long size()const=0;
    ///id of this block
    virtual const char* getId()const=0;
    ///first version
    virtual unsigned char getVersion()const=0;
    ///id in 1.12
    virtual const char* getIdOld()const=0;
    ///if this block needs a glass block under it
    virtual bool getNeedGlass()const=0;
    ///if this block emits light
    virtual bool getDoGlow()const=0;
    ///if this block can be stolen by enderman
    virtual bool getEndermanPickable()const=0;
    ///if this block can be burnt
    virtual bool getBurnable()const=0;
    ///if this block can be used in wall-map
    virtual bool getWallUseable()const=0;

    ///set block id
    virtual void setId(const char*)=0;
    ///set first version
    virtual void setVersion(unsigned char)=0;
    ///set id in 1.12
    virtual void setIdOld(const char*)=0;
    ///set if this block needs a glass block under it
    virtual void setNeedGlass(bool)=0;
    ///set if this block emits light
    virtual void setDoGlow(bool)=0;
    ///set if this block can be stolen by enderman
    virtual void setEndermanPickable(bool)=0;
    ///set if this block can be burnt
    virtual void setBurnable(bool)=0;
    ///set if this block can be used in wall-map
    virtual void setWallUseable(bool)=0;
    ///let *b equal to *this
    void copyTo(AbstractBlock * b) const;
    ///set this block to air
    void clear();
    ///replacement for operator delete
    virtual void destroy()=0;
};
}   //  namespace SlopeCraft
#endif  //  ifndef SLOPECRAFT_CAPI


namespace SlopeCraft {
#ifdef SLOPECRAFTL_CAPI
struct Kernel;
#else
class Kernel;
#endif
}   //  namespace SlopeCraft

namespace SlopeCraft {

/**
 * @brief Minecraft game version
 */
enum gameVersion {
    ///older than 1.12
    ANCIENT=0,
    ///1.12
    MC12=12,
    ///1.13
    MC13=13,
    ///1.14
    MC14=14,
    ///1.15
    MC15=15,
    ///1.16
    MC16=16,
    ///1.17
    MC17=17,
    ///1.18
    MC18=18,
    ///future version
    FUTURE=255
};
///color difference formula used to match colors
enum convertAlgo {
    ///naive RGB
    RGB='r',
    ///RGB with rotation
    RGB_Better='R',
    ///naive HSV formula
    HSV='H',
    ///CIELAB 1994 formula
    Lab94='l',
    ///CIELAB 2000 formula
    Lab00='L',
    ///naive XYZ formula
    XYZ='X',
    AiCvter='A'
};
enum compressSettings {
    ///don't compress
    noCompress=0,
    ///compress in lossless only
    NaturalOnly=1,
    ///compress in lossy only
    ForcedOnly=2,
    ///compress with both lossless and lossy
    Both=3
};
enum glassBridgeSettings {
    ///don't construce bridge
    noBridge=0,
    ///construct bridge
    withBridge=1
};
enum mapTypes {
    ///3D
    Slope=0,
    ///flat
    Flat=1,
    ///map data files
    FileOnly=2,
    ///wall
    Wall=3,
};
enum step {
    ///the instance is created
    nothing,
    ///colorset is configured
    colorSetReady,
    ///map type is set and waitting for image
    wait4Image,
    ///image is ready and ready for converting
    convertionReady,
    ///image is converted and ready for building 3D structure, exporting as file-only map(s) can be done in this step
    converted,
    ///3D structure is built and ready for exporting 3d structure
    builded,
};
enum errorFlag {
    ///no error
    NO_ERROR_OCCUR=-1,
    ///trying to skip steps
    HASTY_MANIPULATION=0x00,
    ///failed when compressing in lossy
    LOSSYCOMPRESS_FAILED=0x01,
    ///color in shadow 3 appears in vanilla map
    DEPTH_3_IN_VANILLA_MAP=0x02,
    ///
    MAX_ALLOWED_HEIGHT_LESS_THAN_14=0x03,
    ///too few color to convert
    USEABLE_COLOR_TOO_FEW=0x04,
    ///the original image is empty
    EMPTY_RAW_IMAGE=0x05,
    ///failed to gzip
    FAILED_TO_COMPRESS=0x06,
    ///failed to remove uncompressed files
    FAILED_TO_REMOVE=0x07,
    ///colorsheet error
    PARSING_COLORMAP_RGB_FAILED=0x10,
    ///colorsheet error
    PARSING_COLORMAP_HSV_FAILED=0x11,
    ///colorsheet error
    PARSING_COLORMAP_Lab_FAILED=0x12,
    ///colorsheet error
    PARSING_COLORMAP_XYZ_FAILED=0x13,
};
enum workStatues {
    ///waiting
    none=-1,

    collectingColors=0x00,
    converting=0x01,
    dithering=0x02,
    //convertFinished=0x03,

    buidingHeighMap=0x10,
    compressing=0x11,
    building3D=0x12,
    constructingBridges=0x13,
    flippingToWall=0x14,

    writingMetaInfo=0x20,
    writingBlockPalette=0x21,
    writing3D=0x22,
    //slopeFinished=0x16,

    writingMapDataFiles=0x30,
    //dataFilesFinished=0x31,
};


#ifndef SLOPECRAFTL_CAPI
class SCL_EXPORT Kernel
{
public:
    Kernel();
    //virtual ~Kernel() {};

///create a kernel object
static Kernel * create();

public:
    static void getColorMapPtrs(const float**,const unsigned char**,int*);
    //full palette
    static const float * getBasicColorMapPtrs();

    static const char * getSCLVersion();

    static unsigned long long mcVersion2VersionNumber(gameVersion);

//can do in nothing:
    ///real size of kernel
    virtual unsigned long long size()=0;
    ///revert to a previous step
    virtual void decreaseStep(step)=0;
    ///replacement for operator delete
    virtual void destroy()=0;
    ///configure colorsheets
    virtual bool setColorSet(const char* _RGB,
                             const char* HSV,
                             const char* Lab,
                             const char* XYZ)=0;


//can do in colorSetReady:
    ///get current step
    virtual step queryStep() const=0;
    ///set map type and blocklist
    virtual bool setType(mapTypes,
                 gameVersion,
                 const bool [64],
                 const AbstractBlock * [64])=0;
    ///get TokiNoBug's url
    virtual void getAuthorURL(int * count,char ** dest) const=0;
    ///get palette (base colors only) in ARGB32
    virtual void getARGB32(unsigned int *) const=0;


//can do in wait4Image:
    ///set original image from ARGB32 matrix (col-major)
    virtual void setRawImage(const unsigned int * src, short rows,short cols)=0;
    ///get accessible color count
    virtual unsigned short getColorCount() const=0;
    ///make a structure that includes all accessible blocks
    virtual void makeTests(const AbstractBlock **,
                       const unsigned char *,
                       const char *,char*)=0;

//can do in convertionReady:
    ///convert original image to map
    virtual bool convert(convertAlgo=RGB_Better,bool dither=false)=0;
    ///get image rows
    virtual short getImageRows() const=0;
    ///get image cols
    virtual short getImageCols() const=0;
    ///query if map is buildable in vanilla survival
    virtual bool isVanilla() const=0;
    ///query if map is a flat one
    virtual bool isFlat() const=0;

//can do in converted:
    ///construct 3D structure
    virtual bool build(compressSettings=noCompress,unsigned short=256,
               glassBridgeSettings=noBridge,unsigned short=3,
               bool fireProof=false,bool endermanProof=false)=0;

    ///get converted image
    virtual void getConvertedImage(short * rows,short * cols,unsigned int * dest) const=0;
    ///export as map data files
    virtual void exportAsData(const char * FolderPath,
                              const int indexStart,
                              int* fileCount,
                              char ** dest) const=0;
    ///get converted map(in mapColor array)
    virtual void getConvertedMap(short * rows,short * cols,unsigned char *) const=0;

//can do in builded:
    ///export map into litematica files (*.litematic)
    virtual void exportAsLitematic(const char * TargetName,
                           const char * LiteName,
                           const char * author,
                           const char * RegionName,
                           char * FileName)const=0;
    ///export map into Structure files (*.NBT)
    virtual void exportAsStructure(const char * TargetName,char * FileName) const=0;

    ///get x,y,z size
    virtual void get3DSize(int & x,int & y,int & z) const=0;

    ///get 3d structure's size
    virtual int getHeight() const=0;
    ///get 3d structure's size
    virtual int getXRange() const=0;
    ///get 3d structure's size
    virtual int getZRange() const=0;
    ///get block count in total and in detail
    virtual void getBlockCounts(int * total, int detail[64]) const=0;
    ///get sum block count
    virtual int getBlockCounts() const=0;
    ///get 3d structure in 3d-matrix (col major)
    virtual const unsigned char * getBuild(int* xSize,int* ySize,int* zSize) const=0;

    ///function ptr to window object
    virtual void setWindPtr(void *)=0;
    ///a function ptr to show progress of converting and exporting
    virtual void setProgressRangeSet(void(*)(void*,int,int,int))=0;
    ///a function ptr to add progress value
    virtual void setProgressAdd(void(*)(void*,int))=0;
    ///a function ptr to prevent window from being syncoped
    virtual void setKeepAwake(void(*)(void*))=0;

    ///a function ptr to show progress of compressing and bridge-building
    virtual void setAlgoProgressRangeSet(void(*)(void*,int,int,int))=0;
    ///a function ptr to add progress value of compressing and bridge-building
    virtual void setAlgoProgressAdd(void(*)(void*,int))=0;

    ///a function ptr to report error when something wrong happens
    virtual void setReportError(void(*)(void*,errorFlag))=0;
    ///a function ptr to report working statue especially when busy
    virtual void setReportWorkingStatue(void(*)(void*,workStatues))=0;

protected:
    ///calling delete is deprecated, use void Kernel::destroy() instead
    void operator delete(void*) {}

};
#endif  //  #ifndef SLOPECRAFTL_CAPI
}

#ifdef SLOPECRAFTL_CAPI
extern "C" {
namespace SlopeCraft
{
    ///create a Kernel object
    Kernel * SCL_EXPORT createKernel();

    void SCL_EXPORT getColorMapPtrs(const float**,const unsigned char**,int*);
    //full palette
    const float * SCL_EXPORT getBasicColorMapPtrs();

    const char * SCL_EXPORT getSCLVersion();

    unsigned long long SCL_EXPORT mcVersion2VersionNumber(gameVersion);

//can do in nothing:
    ///real size of Kernel
    unsigned long long SCL_EXPORT kernelSize(Kernel * k);
    ///revert to a previous step
    void SCL_EXPORT decreaseStep(Kernel * k,step);
    ///replacement for operator delete
    void SCL_EXPORT destroyKernel(Kernel * k);
    ///configure colorsheets
    bool SCL_EXPORT setColorSet(Kernel * k,
                             const char* _RGB,
                             const char* HSV,
                             const char* Lab,
                             const char* XYZ);


//can do in colorSetReady:
    ///get current step
    step SCL_EXPORT queryStep(const Kernel * k);
    ///set map type and blocklist
    bool SCL_EXPORT setType(Kernel * k,
                 mapTypes,
                 gameVersion,
                 const bool [64],
                 const AbstractBlock * [64]);
    ///get TokiNoBug's url
    void SCL_EXPORT getAuthorURL(const Kernel * k,int * count,char ** dest);
    ///get palette (base colors only) in ARGB32
    void SCL_EXPORT getARGB32(const Kernel * k,unsigned int *);


//can do in wait4Image:
    ///set original image from ARGB32 matrix (col-major)
    void SCL_EXPORT setRawImage(Kernel * k,const unsigned int * src, short rows,short cols);
    ///get accessible color count
    unsigned short SCL_EXPORT getColorCount(const Kernel * k);
    ///make a structure that includes all accessible blocks
    void SCL_EXPORT makeTests(Kernel * k,const AbstractBlock **,
                       const unsigned char *,
                       const char *,char*);

//can do in convertionReady:
    ///convert original image to map
    bool SCL_EXPORT convert(Kernel * k,convertAlgo=RGB_Better,bool dither=false);
    ///get image rows
    short SCL_EXPORT getImageRows(const Kernel * k);
    ///get image cols
    short SCL_EXPORT getImageCols(const Kernel * k);
    ///query if map is buildable in vanilla survival
    bool SCL_EXPORT isVanilla(const Kernel * k);
    ///query if map is a flat one
    bool SCL_EXPORT isFlat(const Kernel * k);

//can do in converted:
    ///construct 3D structure
    bool SCL_EXPORT build(Kernel * k,
               compressSettings=noCompress,
               unsigned short=256,
               glassBridgeSettings=noBridge,
               unsigned short=3,
               bool fireProof=false,bool endermanProof=false);

    ///get converted image
    void SCL_EXPORT getConvertedImage(const Kernel * k,short * rows,short * cols,unsigned int * dest);
    ///export as map data files
    void SCL_EXPORT exportAsData(const Kernel * k,const char * FolderPath,
                              const int indexStart,
                              int* fileCount,
                              char ** dest);
    ///get converted map(in mapColor array)
    void SCL_EXPORT getConvertedMap(const Kernel * k,short * rows,short * cols,unsigned char *);

//can do in builded:
    ///export map into litematica files (*.litematic)
    void SCL_EXPORT exportAsLitematic(const Kernel * k,const char * TargetName,
                           const char * LiteName,
                           const char * author,
                           const char * RegionName,
                           char * FileName);
    ///export map into Structure files (*.NBT)
    void SCL_EXPORT exportAsStructure(const Kernel * k,const char * TargetName,char * FileName);

    ///get x,y,z size
    void SCL_EXPORT get3DSize(const Kernel * k,int * x,int * y,int * z);

    ///get 3d structure's size
    int SCL_EXPORT getHeight(const Kernel * k);
    ///get 3d structure's size
    int SCL_EXPORT getXRange(const Kernel * k);
    ///get 3d structure's size
    int SCL_EXPORT getZRange(const Kernel * k);
    ///get block count in total and in detail
    void SCL_EXPORT getBlockCountsInTypes(const Kernel * k,int * total, int detail[64]);
    ///get sum block count
    int SCL_EXPORT getBlockCounts(const Kernel * k);
    ///get 3d structure in 3d-matrix (col major)
    const unsigned char * SCL_EXPORT getBuild(const Kernel * k,int* xSize,int* ySize,int* zSize);

    ///function ptr to window object
    void SCL_EXPORT setWindPtr(Kernel * k,void *);
    ///a function ptr to show progress of converting and exporting
    void SCL_EXPORT setProgressRangeSet(Kernel * k,void(*)(void*,int,int,int));
    ///a function ptr to add progress value
    void SCL_EXPORT setProgressAdd(Kernel * k,void(*)(void*,int));
    ///a function ptr to prevent window from being syncoped
    void SCL_EXPORT setKeepAwake(Kernel * k,void(*)(void*));

    ///a function ptr to show progress of compressing and bridge-building
    void SCL_EXPORT setAlgoProgressRangeSet(Kernel * k,void(*)(void*,int,int,int));
    ///a function ptr to add progress value of compressing and bridge-building
    void SCL_EXPORT setAlgoProgressAdd(Kernel * k,void(*)(void*,int));

    ///a function ptr to report error when something wrong happens
    void SCL_EXPORT setReportError(Kernel * k,void(*)(void*,errorFlag));
    ///a function ptr to report working statue especially when busy
    void SCL_EXPORT setReportWorkingStatue(Kernel * k,void(*)(void*,workStatues));
}   //  namespace SlopeCraft
}   //  extern C
#endif  //  #ifdef SLOPECRAFTL_CAPI

#endif // KERNEL_H
