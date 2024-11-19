//
//  NewRecipeView.swift
//  RecipeSaver
//
//  Created by Caleb Song on 10/20/24.
//

import SwiftUI
import SwiftData

struct NewRecipeView: View{
    @State private var showAddRecipe = false
//    @Binding var recipes: [Recipe]
    @Environment(\.modelContext) private var context
    @Query private var recipes: [RecipeItem]
    
    var body: some View{
        NavigationView {
            Button("Add recipe manually"){
                showAddRecipe = true
            }
            .navigationTitle("New Recipe")
        }
        .navigationViewStyle(.stack)
        .sheet(isPresented: $showAddRecipe){
            AddRecipeView()
        }
    }
}


struct NewRecipeView_Previews: PreviewProvider{
    @State static var recipes: [Recipe] = Recipe.all
    static var previews: some View{
        NewRecipeView()
    }
}
