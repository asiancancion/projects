//
//  ContentView.swift
//  RecipeSaver
//
//  Created by Caleb Song on 10/20/24.
//

import SwiftUI
import SwiftData

struct ContentView: View {
    //idk if i was supposed to add but without it broke
    //@EnvironmentObject var recipesVM: RecipesViewModel
    @Environment(\.modelContext) private var context
    @Query private var recipes: [RecipeItem]
    
    var body: some View {
        TabBar()
    }
}

struct ContentView_Previews: PreviewProvider{
    static var previews: some View{
        ContentView()
    }
}
