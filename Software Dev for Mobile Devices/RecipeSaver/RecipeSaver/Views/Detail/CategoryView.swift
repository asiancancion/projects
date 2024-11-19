//
//  CategoryView.swift
//  RecipeSaver
//
//  Created by Caleb Song on 10/20/24.
//

import SwiftUI
import SwiftData

struct CategoryView: View{
    //@EnvironmentObject var recipesVM: RecipesViewModel
    @Environment(\.modelContext) private var context
    @Query private var recipes: [RecipeItem]
    var category: Category
    
    

    var filteredRecipes: [RecipeItem]{
        return recipes.filter{ $0.category == category.rawValue}
    }
    
    var body: some View{
        ScrollView{
            RecipeList(recipes: filteredRecipes)
        }
        .navigationTitle(category.rawValue + "s")
    }
}


struct CategoryView_Previews: PreviewProvider{
    @State static var recipes: [Recipe] = Recipe.all
    static var previews: some View{
        CategoryView(category: Category.side)
    }
}
