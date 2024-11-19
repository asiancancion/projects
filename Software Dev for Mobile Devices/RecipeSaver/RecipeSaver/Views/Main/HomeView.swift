//
//  HomeView.swift
//  RecipeSaver
//
//  Created by Caleb Song on 10/20/24.
//

import SwiftUI
import SwiftData

struct HomeView: View{
//    @EnvironmentObject var recipesVM: RecipesViewModel
//    @Binding var recipes: [Recipe]
    @Environment(\.modelContext) private var context
    @Query private var recipes: [RecipeItem]
    var body: some View{
        NavigationView {
            List {
                ForEach(recipes) { recipe in
                    NavigationLink(destination: RecipeView(recipe: recipe)) {
                        RecipeCard(recipe: recipe)
                        
                    }
                }
                .onDelete(perform: deleteRecipe) // Enables swipe-to-delete
            }
            .listStyle(PlainListStyle())
            .navigationTitle("My Recipes")
            
        }
        .navigationViewStyle(.stack)
    }
    private func deleteRecipe(at offsets: IndexSet) {
        for index in offsets{
            let delete = recipes[index]
            context.delete(delete)
        }
    }
}


struct HomeView_Previews: PreviewProvider{
    static var previews: some View{
        HomeView()
    }
    
}
