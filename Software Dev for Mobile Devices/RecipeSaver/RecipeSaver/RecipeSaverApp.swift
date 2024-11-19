//
//  RecipeSaverApp.swift
//  RecipeSaver
//
//  Created by Caleb Song on 10/20/24.
// Documentation: Used videos on writeup, got EI from Lt Col Maher on 10/22. Also used GPT for things like refactoring code with bindings, fixing lists, and general debugging: https://chatgpt.com/share/67192502-5fec-800e-b795-b956e83f097b
// Additional Features: Category and Favorites Pages
//

import SwiftUI
import SwiftData

@main
struct RecipeSaverApp: App {
//    @StateObject var recipesViewModel = RecipesViewModel()
    
    var body: some Scene {
        WindowGroup {
            ContentView()
        }
        .modelContainer(for: RecipeItem.self)
    }
}
