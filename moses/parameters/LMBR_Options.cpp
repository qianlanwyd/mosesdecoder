// -*- mode: c++; indent-tabs-mode: nil; tab-width: 2 -*-
#include "LMBR_Options.h"

namespace Moses {

  bool
  LMBR_Options::
  init(Parameter const& param)
  {
    param.SetParameter(enabled, "lminimum-bayes-risk", false);
    
    param.SetParameter(ratio, "lmbr-r", 0.6f);
    param.SetParameter(precision, "lmbr-p", 0.8f);
    param.SetParameter(map_weight, "lmbr-map-weight", 0.0f);
    param.SetParameter(pruning_factor, "lmbr-pruning-factor", size_t(30));
    param.SetParameter(use_lattice_hyp_set, "lattice-hypo-set", false);
    
    PARAM_VEC const* params = param.GetParam("lmbr-thetas");
    if (params) theta = Scan<float>(*params);
    
    return true;
  }
  
}
