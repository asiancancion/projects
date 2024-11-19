//
//  RecipesViewModel.swift
//  RecipeSaver
//
//  Created by Caleb Song on 10/20/24.
//

import Foundation


class RecipesViewModel: ObservableObject{
    @Published private(set) var recipes: [Recipe] = []
    
    init(){
        recipes = Recipe.all
    }
    
    func addRecipe(recipe: Recipe){
        recipes.append(recipe)
    }
}
