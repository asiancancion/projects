//
//  FavortiesView.swift
//  RecipeSaver
//
//  Created by Caleb Song on 10/20/24.
//

import SwiftUI
import SwiftData

struct FavoritesView: View{
    @Environment(\.modelContext) private var context
    @Query private var recipes: [RecipeItem]
    var body: some View{
        NavigationView {
            if favoritedRecipes.isEmpty{
                Text("You haven't favorited any recipes yet").padding().navigationTitle("Favorites")
            }
            else{
//                List {
//                    ForEach(favoritedRecipes) { recipe in
//                        NavigationLink(destination: RecipeView(recipe: recipe)) {
//                            RecipeCard(recipe: recipe)
//                            
//                        }
//                    }
//                }
                ScrollView{
                    RecipeList(recipes: favoritedRecipes)
                }
                .navigationTitle("Favorites")
            }
            
        }
        .navigationViewStyle(.stack)
    }
    private var favoritedRecipes: [RecipeItem]{
        return recipes.filter{$0.favorite}
    }
}


struct FavoritesView_Previews: PreviewProvider{
    static var previews: some View{
        FavoritesView()
    }
}
