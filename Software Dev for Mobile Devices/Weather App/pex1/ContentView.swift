/* Name: Caleb Song
 * Assignment: Pex 1 Weather App
 * Feature(s) Added: Rotating arrow based on wind direction
 * Documentation Statement:
 JSON Model - to decode the nested JSON model asked ChatGPT: 
https://chatgpt.com/share/66f4b303-77b4-800e-b008-cff18b97e434
 Color Gradiant - https://chatgpt.com/share/66f4dcca-4850-800e-9752-4c311fc05106
Debugging code and adding rotating arrow - https://chatgpt.com/share/66f6014b-4e54-800e-afcc-cbf02840ab41
 Please wait like 1-2 minutes potentially sometimes the app is slow
 
 */

import SwiftUI
import CoreLocation

struct ContentView: View {
    //Structs and initialized variables
    @State private var weather: Weather = Weather()
    @State private var location: Location = Location(results: [])
    @State private var coordinates: Coordinates = Coordinates(results: [])
    @State private var current: String = ""
    private let service = PostsService()
    @State private var latitude: CLLocationDegrees = 0.0
    @State private var longitude: CLLocationDegrees =  0.0
    @State private var temperatureCelsius: Float = 0.0
    //Default city to add statically
    @State private var cityName: String = "Cupertino"
    @State var cityList: [CityData] = [CityData(id: UUID(), city: "Cupertino")]
    @State var showAddCity = false
    //to collect user location need locationManager struct
    @ObservedObject var locationManager: LocationManager
    var body: some View{
        TabView{
            //displays all cities
            ForEach(cityList, id:\.self){
                city in
                ZStack{
                    LinearGradient(
                        gradient: Gradient(colors: [.blue, .red]),
                        startPoint: .top,
                        endPoint: .bottom
                    )
                    .ignoresSafeArea(.all)
                    
                    VStack{
                        HStack{
                            //top portion of view
                            Spacer()
                            Text(city.city).font(.system(size: 35))
                            Spacer()
                            //button to add cities
                            Button(action:{showAddCity = true}){
                                Text("+")
                                    .padding()
                                    .foregroundColor(Color.black)
                                    .font(.system(size:20))
                            }
                            .sheet(isPresented: $showAddCity) {
                                AddCityView(cityList: $cityList, didAddCity: { city in
                                    cityList.append(CityData(id: UUID(), city: city))
                                    showAddCity = false
                                })
                            }
                        }
                        //Day temperature in Farenheit and Celsius
                        Text("\(weather.currentWeather.temperatureFarenheit, specifier: "%.0f")°F").font(.system(size:40)).bold()
                        Text("\(temperatureCelsius, specifier: "%.1f")°C").font(.system(size:20))
                        Spacer()
                        //3 Day Forecast stacks DayView for the 3-day data
                        Text("3 Day Forecast").font(.system(size: 25))
                        DayView(weather: $weather)
                        Spacer()
                        //if windspeed is greater than 0 displays the wind symbol and direction with arrow
                        if(weather.currentWeather.wind_speed > 0){
                            HStack{
                                Image(systemName: "wind").font(.system(size:50))
                                Image(systemName: "arrow.up").font(.system(size:50)).rotationEffect(.degrees(Double(weather.currentWeather.wind_direction)))
                            }
                        }
                        //prints data of wind
                        Text("Wind out of \(weather.currentWeather.wind_direction)°")
                        Text("Current Windspeed: \(weather.currentWeather.wind_speed, specifier: "%.1f") knots")
                    }
                    
                }
            //reoccuring tasks to collect data from JSON
            .task{
                coordinates = await service.getLatLong(cityName: city.city)
                self.latitude = coordinates.results.first?.geometry.latitude ?? 0.0
                self.longitude = coordinates.results.first?.geometry.longitude ?? 0.0
                weather = await service.fetchUsers(latitude: self.latitude, longitude: self.longitude)
                if let currentLocation = locationManager.current{
                    latitude = currentLocation.coordinate.latitude
                    longitude = currentLocation.coordinate.longitude
                }
                location = await service.getCity(latitude: latitude, longitude: longitude)
                self.current = location.results.first?.components.city ?? "Cupertino"
                temperatureCelsius = (weather.currentWeather.temperatureFarenheit-32)*(5/9)
                if !cityList.contains(where: {$0.city == current}){
                    cityList.append(CityData(id: UUID(), city: current))
                }
            }
            }
        }
        //allow for switching between cities with swipes
        .tabViewStyle(PageTabViewStyle())
        .padding()
    }
}



#Preview {
    ContentView(locationManager: LocationManager())
}
