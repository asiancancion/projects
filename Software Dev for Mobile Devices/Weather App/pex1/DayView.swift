//
//  DayView.swift
//  pex1
//
//  Created by Caleb Song on 9/25/24.
//

import SwiftUI
import CoreLocation

struct DayView: View {
    @Binding var weather: Weather
    var body: some View{
                HStack{
                //goes through the 3 day data and displays information
                ForEach(0..<weather.dailyWeather.days.count, id: \.self) { index in
                    VStack{
                        //based on weather code displays different weather symbols
                        Text("\(weather.dailyWeather.days[index])").font(.system(size: 15))
                        if (weather.dailyWeather.weatherCode[index] == 0){
                            Image(systemName: "sun.max.fill")
                        }
                        if (weather.dailyWeather.weatherCode[index] > 0 && weather.dailyWeather.weatherCode[index] < 4){
                            Image(systemName: "cloud.fill")
                        }
                        if (weather.dailyWeather.weatherCode[index] == 45 || weather.dailyWeather.weatherCode[index] == 48){
                            Image(systemName: "cloud.fog.fill")
                        }
                        if (weather.dailyWeather.weatherCode[index] == 51 || weather.dailyWeather.weatherCode[index] == 53 ||
                            weather.dailyWeather.weatherCode[index] == 55 ||
                            weather.dailyWeather.weatherCode[index] == 56 || weather.dailyWeather.weatherCode[index] == 57){
                            Image(systemName: "cloud.drizzle.fill")
                        }
                        if (weather.dailyWeather.weatherCode[index] == 61 || weather.dailyWeather.weatherCode[index] == 63 ||
                            weather.dailyWeather.weatherCode[index] == 65 ||
                            weather.dailyWeather.weatherCode[index] == 66 ||
                            weather.dailyWeather.weatherCode[index] == 67 ||
                            weather.dailyWeather.weatherCode[index] == 80 ||
                            weather.dailyWeather.weatherCode[index] == 81 ||
                            weather.dailyWeather.weatherCode[index] == 82){
                            Image(systemName: "cloud.rain.fill")
                        }
                        if (weather.dailyWeather.weatherCode[index] == 71 || weather.dailyWeather.weatherCode[index] == 73 ||
                            weather.dailyWeather.weatherCode[index] == 75 ||
                            weather.dailyWeather.weatherCode[index] == 77 ||
                            weather.dailyWeather.weatherCode[index] == 85 ||
                            weather.dailyWeather.weatherCode[index] == 86){
                            Image(systemName: "cloud.snow.fill")
                        }
                        if (weather.dailyWeather.weatherCode[index] == 95 || weather.dailyWeather.weatherCode[index] == 96 ||
                            weather.dailyWeather.weatherCode[index] == 99){
                            Image(systemName: "cloud.bolt.rain.fill")
                        }
                        
                        //prints high and low
                        Text("High: \(weather.dailyWeather.temperatureMax[index], specifier: "%.1f")°F").font(.system(size: 15))
                        Text("Low: \(weather.dailyWeather.temperatureMin[index], specifier: "%.1f")°F").font(.system(size: 15))
                    }
                }
            }
            .padding().background(Color.clear).listRowBackground(Color.clear)
    }
        
    
           
    
        
    }

//#Preview {
//    DayView()
//}
