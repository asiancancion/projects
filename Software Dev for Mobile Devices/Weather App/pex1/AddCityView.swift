//
//  AddCityView.swift
//  pex1
//
//  Created by Caleb Song on 9/25/24.
//

import SwiftUI

struct AddCityView: View {
    @State private var city = ""
    @Binding var cityList: [CityData]
    
    var didAddCity: (String) -> ()
    
    var body: some View {
        Form{
            //Allows user to add a city
            TextField("Add City", text: $city)
            Button(action: {didAddCity(city)}){
                Text("Add City")
            }.navigationTitle("Add City")

        }
        
        
        List {
            //goes through current list of cities and prints in a list
            ForEach(cityList, id: \.id) { cityData in
                Text(cityData.city)
            }.onDelete(perform: deleteItem)
        }.navigationTitle("View and Remove Cities")
    }
    private func deleteItem(at indexSet: IndexSet){
        cityList.remove(atOffsets: indexSet)
    }
    
}

//#Preview {
//    AddContactView()
//}
