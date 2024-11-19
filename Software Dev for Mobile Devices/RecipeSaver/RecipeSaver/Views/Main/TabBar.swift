//
//  TabBar.swift
//  RecipeSaver
//
//  Created by Caleb Song on 10/20/24.
//

import SwiftUI
import SwiftData

struct TabBar: View{
    //idk if i was supposed to add but without it broke
    //@EnvironmentObject var recipesVM: RecipesViewModel
//    @State private var recipes: [Recipe] = Recipe.all
    @Query private var recipes: [RecipeItem]
    var body: some View{
        TabView{
            HomeView().tabItem{
                Label("Home", systemImage: "house")
            }
            
            CategoriesView().tabItem{
                Label("Categories", systemImage: "square.fill.text.grid.1x2")
            }
            NewRecipeView().tabItem{
                Label("New", systemImage: "plus")
            }
            
            FavoritesView().tabItem{
                Label("Favorites", systemImage: "heart")
            }
        }
    }
}


struct TabBar_Previews: PreviewProvider{
    static var previews: some View{
        TabBar()
    }
}
