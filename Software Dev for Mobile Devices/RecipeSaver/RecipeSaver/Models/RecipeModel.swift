//
//  RecipeModel.swift
//  RecipeSaver
//
//  Created by Caleb Song on 10/20/24.
//


//Going to replace this with a swift data item
import Foundation

//enum Category: String, CaseIterable, Identifiable {
//    var id: String { self.rawValue}
//    case breakfast = "Breakfast"
//    case soup = "Soup"
//    case salad = "Salad"
//    case appetizer = "Appetizer"
//    case main = "Main"
//    case side = "Side"
//    case dessert = "Dessert"
//    case snack = "Snack"
//    case drink = "Drink"
//}

struct Recipe: Identifiable{
    let id = UUID()
    let name: String
    let image: String
    let recipeDescription: String
    let ingredients: String
    let directions: String
    let category: Category.RawValue
    let datePublished: String
    let url: String
    
}


extension Recipe{
    static let all: [Recipe] = [
        Recipe(name: "Taco", image: "https://www.onceuponachef.com/images/2023/08/Beef-Tacos.jpg", recipeDescription: "tacos", ingredients: "meat\nlettuce\ntortilla", directions: "put the ingredients in the shell", category: "Main", datePublished: "2024-10-20", url: "https://feelgoodfoodie.net/recipe/ground-beef-tacos-napa-cabbage-guacamole/"),
        Recipe(name: "Fries", image: "https://www.recipetineats.com/tachyon/2022/09/Fries-with-rosemary-salt_1.jpg?resize=900%2C1125&zoom=1", recipeDescription: "fries", ingredients: "potato", directions: "put the fries in the bag", category: "Side", datePublished: "2024-10-19", url: "https://www.recipetineats.com/french-fries/")
    ]
}
