DATA LOADING
At program strart
  Load airports.csv into vector<airports>
  Use struct airports with fields:
    ident, type, name, elevation_ft, continent, iso_country,
    iso_region, municipality, icao_code, iata_code, gps_code,
    local_code, latitude, longitude.
SEARCHING
Three search functions:
  By country code ( e.g. US, GB )
  By Partial Flight name ( e.g. Harold Miller, New York )
  Bt IATA code ( e.g. OCA, CUX )
Each search: 
  reads user input
  loops through the airport vector
  prints the matching airports using the printAirports function
DISPLAYING DATA
  Using printAirport(const Airport& a) 
  implimenting counting by type
    Counting how many airports there are by type ( e.g. heliport, small etc. )
    Print those counts
SAVING DATA
  write all airports (including the added ones) to airports_updated.csv
  Formatting it like the original CSV
USER INTERFACE
  Simple menu driven console app
====== Nottingham SkyRoute Explorer ======
1. Search airports by country
2. Search airports by name
3. Search by IATA code
4. Count airports by type
5. Add a new airport
6. Advanced options(radius search, nearest airport, high / low elevation, etc.)
7. Save airports
8. Exit
==========================================
  loop the menu until the user chooses to exit
  handle invalid inputs
