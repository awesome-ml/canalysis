/*
 * BSD 3-Clause License
 * Canalysis (Crime Analysis) 0.1.0
 * Copyright (c) 2016, Matt Perez, all rights reserved.
 *
 * This source is licensed under the BSD 3-Clause License.
 * The license can be found in the main directory for more
 * information about using this program.
*/

#include <iostream>

#include "canalysis.h"

namespace canalysis {

Canalysis::Canalysis(std::string csvfile,
                     unsigned int crime_column,
                     unsigned int lat_column,
                     unsigned int long_column)
{
   _csvfile = csvfile;
   _crime_coloumn = crime_column;
   _lat_column = lat_column;
   _long_column = long_column;
}

std::pair<double, double> Canalysis::predictedLocations(double lat_values, double long_values)
{
   double precise_lat = boost::lexical_cast<double>(lat_values);
   double precise_long = boost::lexical_cast<double>(long_values);

   Layer layer(precise_lat, precise_long);
   std::cout << precise_lat << std::endl;
}

std::istream &operator>>(std::istream &file, Parser &parser)
{
   parser.getColumnFields(file);
   return file;
}

void Canalysis::model()
{
   Parser parser;
   Writer writer;
   std::fstream file(_csvfile);

   while (file >> parser){
      std::string crime_c = parser[_crime_coloumn];
      std::string lat_c = parser[_lat_column];
      std::string long_c = parser[_long_column];

      if (crime_c.empty() || lat_c.empty() || long_c.empty())
         std::cout << "[!] Error: One or more fields are empty" << std::endl;

      double lat_values = atof(lat_c.c_str());
      double long_values = atof(long_c.c_str());
      std::pair<double, double> prediction = predictedLocations(lat_values, long_values);
      //writer.exportData("templates/data/prediction.csv", prediction.first, prediction.second);
   }
}

}
