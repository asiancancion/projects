//
//  RecipeItem.swift
//  RecipeSaver
//
//  Created by Caleb Song on 10/22/24.
//

import Foundation
import SwiftData


enum Category: String, CaseIterable, Identifiable {
    var id: String { self.rawValue}
    case breakfast = "Breakfast"
    case soup = "Soup"
    case salad = "Salad"
    case appetizer = "Appetizer"
    case main = "Main"
    case side = "Side"
    case dessert = "Dessert"
    case snack = "Snack"
    case drink = "Drink"
}

@Model
class RecipeItem: Identifiable{
    var id = UUID()
    var name: String
    var image: Data?
    var recipeDescription: String
    var ingredients: String
    var directions: String
    var category: String
    var datePublished: String
    var favorite: Bool
    
    init (name: String, image: Data?, recipeDescription: String, ingredients: String, directions: String, category: Category, datePublished: String, favorite: Bool){
        self.id = UUID()
        self.name = name;
        self.image = image;
        self.recipeDescription = recipeDescription;
        self.ingredients = ingredients;
        self.directions = directions;
        self.category = category.rawValue;
        self.datePublished = datePublished;
        self.favorite = favorite;
        
    }
    
    var categoryEnum: Category? {
        return Category(rawValue: category)
    }
}
