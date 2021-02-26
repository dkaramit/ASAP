#ifndef FFANN_head
#define FFANN_head

#include<cmath>
#include<random>
#include<vector>
#include<array>


#include "FFANN_class.hpp"
#include "FFANN_const.hpp"
#include "FFANN_params.hpp"

#include "FFANN_derivatives.hpp"
#include "FFANN_call.hpp"
#include "FFANN_backProp.hpp"

#include "FFANN_numerical_derivative.hpp"


#include "FFANN_aux.hpp"

// Need these for training
#include "FFANN_SGD.hpp"
#include"FFANN_loss.hpp"
#include"Vanilla_SGD.hpp"
#include"RMSprop_SGD.hpp"
#include"AdaDelta_SGD.hpp"
#include"Adam_SGD.hpp"


#endif