/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          Module              DESCRIPTION                             *
 ** 22/09/2013    Hardware Composer   Responsible for processing some         *
 **                                   Hardware layers. These layers comply    *
 **                                   with display controller specification,  *
 **                                   can be displayed directly, bypass       *
 **                                   SurfaceFligner composition. It will     *
 **                                   improve system performance.             *
 ******************************************************************************
 ** File: SprdHWLayer.h               DESCRIPTION                             *
 **                                   Mainly responsible for filtering HWLayer*
 **                                   list, find layers that meet OverlayPlane*
 **                                   and PrimaryPlane specifications and then*
 **                                   mark them as HWC_OVERLAY.               *
 ******************************************************************************
 ******************************************************************************
 ** Author:         zhongjun.chen@spreadtrum.com                              *
 *****************************************************************************/


#ifndef _SPRD_HWLAYER_H_
#define _SPRD_HWLAYER_H_

#include <hardware/hardware.h>
#include <hardware/hwcomposer.h>
#include <utils/RefBase.h>
#include <cutils/atomic.h>
#include <cutils/log.h>
#include "gralloc_priv.h"

#include "SprdFrameBufferHAL.h"

using namespace android;

/*
 *  YUV format layer info.
 * */
struct sprdYUV {
    uint32_t w;
    uint32_t h;
    uint32_t format;
    uint32_t y_addr;
    uint32_t u_addr;
    uint32_t v_addr;
};

/*
 *  Available layer rectangle.
 * */
struct sprdRect {
    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t h;
};

enum layerType {
    LAYER_OSD = 1,
    LAYER_OVERLAY,
    LAYER_INVALIDE
};


/*
 *  Android layers info from Android Framework is not enough,
 *  here, SprdHWLayer object just add some info.
 * */
class SprdHWLayer
{
public:
    SprdHWLayer()
        : mAndroidLayer(0), mLayerType(LAYER_INVALIDE), 
          mFormat(-1),
          mLayerIndex(-1),
          mSprdLayerIndex(-1),
          mDebugFlag(0)
    {

    }
    ~SprdHWLayer()
    {

    }

    inline bool InitCheck()
    {
        return (mAndroidLayer->compositionType == HWC_OVERLAY);
    }

    inline int getLayerIndex()
    {
        return mLayerIndex;
    }

    inline int getSprdLayerIndex()
    {
        return mSprdLayerIndex;
    }

    inline hwc_layer_1_t *getAndroidLayer()
    {
        return mAndroidLayer;
    }


    inline enum layerType getLayerType()
    {
        return mLayerType;
    }


    inline int getLayerFormat()
    {
        return mFormat;
    }

    inline struct sprdRect *getSprdSRCRect()
    {
        return &srcRect;
    }

    inline struct sprdYUV *getSprdSRCYUV()
    {
        return &srcYUV;
    }

    inline struct sprdRect *getSprdFBRect()
    {
        return &FBRect;
    }

    bool checkRGBLayerFormat();
    bool checkYUVLayerFormat();

private:
    friend class SprdHWLayerList;

    hwc_layer_1_t *mAndroidLayer;
    enum layerType mLayerType;
    int mFormat;
    int mLayerIndex;
    int mSprdLayerIndex;
    struct sprdRect srcRect;
    struct sprdRect FBRect;
    struct sprdYUV  srcYUV;
    bool mDirectDisplayFlag;
    int mDebugFlag;

    inline void setAndroidLayer(hwc_layer_1_t *l)
    {
        mAndroidLayer = l;
    }

    inline void setLayerIndex(unsigned int index)
    {
        mLayerIndex = index;
    }

    inline void setSprdLayerIndex(unsigned int index)
    {
        mSprdLayerIndex = index;
    }

    inline void setLayerType(enum layerType t)
    {
        mLayerType = t;
    }

    inline void setLayerFormat(int f)
    {
        mFormat = f;
    }
};

#endif
