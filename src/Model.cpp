// Copyright (c) 2021 Johannes Delport
// This code is licensed under MIT license (see LICENSE for details)

#include "JoSIM/Model.hpp"
#include "JoSIM/Misc.hpp"
#include "JoSIM/Errors.hpp"
#include "JoSIM/TypeDefines.hpp"

using namespace JoSIM;

void Model::parse_model(
  const std::pair<tokens_t, string_o> &s, 
  vector_pair_t<Model, string_o> &models, const param_map &p) {
  // Ensure the model conforms to correct syntax
  if(s.first.size() < 3) {
    Errors::model_errors(
      ModelErrors::BAD_MODEL_DEFINITION, Misc::vector_to_string(s.first));
  }
  // Create a model that will be stored
  Model temp;
  // The second token is the model label
  temp.set_modelName(s.first.at(1));
  // The third token needs to start with "JJ" for this to be valid
  if(s.first.at(2).compare(0, 2, "JJ") != 0) {
    Errors::model_errors(
      ModelErrors::UNKNOWN_MODEL_TYPE, Misc::vector_to_string(s.first));
  }
  // Create a temporary tokens variable containing the model parameters
  tokens_t tokens(s.first.begin() + 2, s.first.end());
  tokens = Misc::tokenize(
    Misc::vector_to_string(tokens).substr(2), "=(), ");
  // Sanity check, there should be an even number of tokens (parameter=value)
  if (tokens.size() % 2 != 0) {
    Errors::model_errors(
      ModelErrors::BAD_MODEL_DEFINITION, Misc::vector_to_string(s.first));
  }
  // Loop through the parameter tokens
  for (int i = 0; i < tokens.size(); i += 2) {
    // Every even odd token should be a value (otherwise complain)
    float value = parse_param(tokens.at(i + 1), p, s.second);
    if(std::isnan(value)) {
      Errors::model_errors(
      ModelErrors::BAD_MODEL_DEFINITION, Misc::vector_to_string(s.first));
    }
    // Assign the relevant model parameters
    if (tokens.at(i) == "VG" || tokens.at(i) == "VGAP"){
      temp.set_voltageGap(value);
    } else if (tokens.at(i) == "IC" || tokens.at(i) == "ICRIT") {
      temp.set_criticalCurrent(value);
    } else if (tokens.at(i) == "RTYPE") {
      temp.set_resistanceType((int)value);
    } else if (tokens.at(i) == "RN") {
      temp.set_normalResistance(value);
    } else if (tokens.at(i) == "R0") {
      temp.set_subgapResistance(value);
    } else if (tokens.at(i) == "CAP" || tokens.at(i) == "C") {
      temp.set_capacitance(value);
    } else if (tokens.at(i) == "T") {
      temp.set_temperature(value);
    } else if (tokens.at(i) == "TC") {
      temp.set_criticalTemperature(value);
    } else if (tokens.at(i) == "DELV") {
      temp.set_deltaV(value);
    } else if (tokens.at(i) == "D") {
      temp.set_transparency(value);
    } else if (tokens.at(i) == "ICFACT" || tokens.at(i) == "ICFCT") {
      temp.set_criticalToNormalRatio(value);
    } else if (tokens.at(i) == "PHI") {
      temp.set_phaseOffset(value);
    }
  }

  models.emplace_back(std::make_pair(temp, s.second));
}