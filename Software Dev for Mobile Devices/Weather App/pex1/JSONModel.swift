//
//  JSONModel.swift
//  pex1
//
//  Created by Caleb Song on 9/23/24.
//

import Foundation
import CoreLocation

//Structs to decode weather data
struct Weather:Decodable{
    var latitude: Float
    var longitude: Float
    var currentWeather: CurrentWeather
    var dailyWeather: DailyWeather
    
    init(){
        latitude = 0.0
        longitude = 0.0
        currentWeather = CurrentWeather()
        dailyWeather = DailyWeather()
        
    }
    
    enum CodingKeys: String, CodingKey{
        case latitude = "latitude"
        case longitude = "longitude"
        case currentWeather = "current"
        case dailyWeather = "daily"
    }
}
    
struct CurrentWeather: Decodable{
    var temperatureFarenheit: Float
    var wind_speed: Float
    var wind_direction: Int
    
    init(){
        temperatureFarenheit = 0.0
        wind_speed = 0.0
        wind_direction = 0
    }
    enum CodingKeys: String, CodingKey{
        case temperatureFarenheit = "temperature_2m"
        case wind_speed = "wind_speed_10m"
        case wind_direction = "wind_direction_10m"
    }
    
}
    
struct DailyWeather: Decodable{
    var days: [String]
    var weatherCode: [Int]
    var temperatureMax: [Float]
    var temperatureMin: [Float]
    
    init(){
        days = []
        weatherCode = []
        temperatureMax = []
        temperatureMin = []
    }
    enum CodingKeys: String, CodingKey{
        case days = "time"
        case weatherCode = "weather_code"
        case temperatureMax = "temperature_2m_max"
        case temperatureMin = "temperature_2m_min"
    }
    
    
}


//structs to decode cities from lat long
struct Location: Decodable{
    var results: [ResultsCity]
    
    enum CodingKeys: String, CodingKey{
        case results = "results"
    }
}

struct ResultsCity: Decodable{
    var components: Components
    
    enum CodingKeys: String, CodingKey{
        case components = "components"
    }
}

struct Components: Decodable{
    var city: String
    
    enum CodingKeys: String, CodingKey{
        case city = "city"
    }
}


//struct to collect lat long from cities used for to get user's location
struct Coordinates: Decodable{
    var results: [Results]

    enum CodingKeys: String, CodingKey{
        case results = "results"
    }
}

struct Results: Decodable{
    var geometry: Geometry

    enum CodingKeys: String, CodingKey{
        case geometry = "geometry"
    }
}

struct Geometry: Decodable{
    var latitude: Double
    var longitude: Double
    
    enum CodingKeys: String, CodingKey{
        case latitude = "lat"
        case longitude = "lng"
    }
}

struct PostsService{
    private func fetch<T:Decodable>(type: T.Type, from urlString: String) async -> T?{
        guard let url = URL(string: urlString)else{
            return nil
        }
        do{
            let (data,_) = try await URLSession.shared.data(from: url)
            return try JSONDecoder().decode(type, from:data)
        }catch{
            return nil
        }
    }
    
    func fetchUsers(latitude: CLLocationDegrees, longitude: CLLocationDegrees) async -> Weather{
        await fetch(type:Weather.self, from:"https://api.open-meteo.com/v1/forecast?latitude=\(latitude)&longitude=\(longitude)&current=temperature_2m,weather_code,wind_speed_10m,wind_direction_10m&daily=weather_code,temperature_2m_max,temperature_2m_min&temperature_unit=fahrenheit&wind_speed_unit=kn&forecast_days=3") ?? Weather()
        
    
    }
    func getCity(latitude: CLLocationDegrees, longitude: CLLocationDegrees) async -> Location{
        await fetch(type:Location.self, from:"https://api.opencagedata.com/geocode/v1/json?q=\(latitude)%2C\(longitude)&key=63beaaffc61949819a92dbf202bd892e") ?? Location(results: [])
    }
    func getLatLong(cityName: String) async -> Coordinates{
            await fetch(type:Coordinates.self, from:"https://api.opencagedata.com/geocode/v1/json?q=\(cityName)&key=63beaaffc61949819a92dbf202bd892e") ?? Coordinates(results: [])
        }
    
    
    
    
}



