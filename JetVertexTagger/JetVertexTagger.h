#ifndef _JETVERTEXTAGGER_
#define _JETVERTEXTAGGER_


#include "TNamed.h"
#include "TFile.h"
#include "TString.h"
#include "TH2F.h"
#include <iostream>
#include <vector>
#include <math.h> 

class JVTTrack;

class JetVertexTagger : public TNamed{
    public:

        // constructor
        JetVertexTagger(const float &jvt_cut, const TString filein);
        // destructor
        ~JetVertexTagger();

        // init method: call this for each new event
        void init(const std::vector<float> &trk_pt, const std::vector<float> &trk_z0_wrtPV, const std::vector<std::vector<int> > &vxp_trk_index);

        // actual worker
        bool operator()(const float jet_pt, const std::vector<int> assoc_trk_indices);

        // setters 
        inline void setDebug(bool debug){
            debug_ = debug;
        }

        // helpers and info
        float corrJVF(){return corrJVF_;}
        float JVT()    {return JVT_;}
        float RpT()    {return RpT_;}

        #ifdef JETVERTEXTAGGER_STANDALONE
        ClassDef(JetVertexTagger,1);
        #endif

    private: 
        bool                    debug_;
        bool                    goodfile_;
        bool                    goodhisto_;
        TFile*                  file_;
        TH2F*                   likelihood_;
        TString                 likelihood_name_;
        std::vector<JVTTrack*>  trks_;
        float                   jvt_cut_;
        int                     tot_n_pu_tracks_;
        float                   corrJVF_;
        float                   RpT_;
        float                   JVT_;

        // consts
        const float k_z0_cut_;
        const float k_corrJVF_scale_fact_;

};


class JVTTrack {
    public:
        JVTTrack(float pt, float z0_wrtPV): pt_(pt) ,  z0_wrtPV_(z0_wrtPV), origin_(-1){};

        float pt_;
        float z0_wrtPV_;
        float origin_;
};

#endif

