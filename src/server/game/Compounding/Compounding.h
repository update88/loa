#ifndef _H_COMPOUNDING_
#define _H_COMPOUNDING_

#define MAX_COMPOUND_REAGENT 8
#define MAX_COMPOUND_ITEM 4

struct RecipeCompound
{
    uint32 reagent[MAX_COMPOUND_REAGENT];
    uint32 reagentCount[MAX_COMPOUND_REAGENT];
    uint32 item[MAX_COMPOUND_ITEM];
    uint32 itemCount[MAX_COMPOUND_ITEM];
    uint32 reqClass;
    uint32 reqSkill;
    uint32 reqSkillValue;
    uint32 skillUpYellow;
    uint32 skillUpGreen;
    uint32 reqSpellFocus;
    uint32 reqTotem1;
    uint32 reqTotem2;
    uint32 ReqTool1;
    uint32 ReqTool2;
    uint32 cooldown;
    uint32 cdCategory;
};

struct GemCompound
{
    uint32 rawStone;
    uint32 count;
    uint32 gem;
    float chance;
};

struct EnchantCompound
{
    uint32 enchant;
    uint32 duration;
    uint32 _class;
    uint32 subclass;
    uint32 inventoryType;
    uint32 reagent[MAX_COMPOUND_REAGENT];
    uint32 count[MAX_COMPOUND_REAGENT];
    uint32 reqSkill;
    uint32 reqSkillValue;
};

struct SocketCompound
{
    uint32 stone;
    uint32 count;
    uint32 maxItemLevel;
};

typedef std::multimap<uint32, RecipeCompound> RecipeCompoundMap;
typedef std::pair<RecipeCompoundMap::const_iterator, RecipeCompoundMap::const_iterator> RecipeCompoundBounds;
typedef std::multimap<uint32, GemCompound> GemCompoundMap;
typedef std::pair<GemCompoundMap::const_iterator, GemCompoundMap::const_iterator> GemCompoundBounds;
typedef std::multimap<uint32, EnchantCompound> EnchantCompoundMap;
typedef std::pair<EnchantCompoundMap::const_iterator, EnchantCompoundMap::const_iterator> EnchantCompoundBounds;
typedef std::multimap<uint32, SocketCompound> SocketCompoundMap;
typedef std::pair<SocketCompoundMap::const_iterator, SocketCompoundMap::const_iterator> SocketCompoundBounds;

struct Reagent
{
    uint32 reagent[MAX_COMPOUND_REAGENT];
    uint32 count[MAX_COMPOUND_REAGENT];
};

class CompoundMgr
{
public:
    static CompoundMgr* instance()
    {
        static CompoundMgr instance;
        return &instance;
    }
    CompoundMgr() { }
    ~CompoundMgr() { }
    void Load();
    RecipeCompoundBounds GetRecipeCompoundBounds(uint32 reagent) const;
    GemCompoundBounds GetGemCompoundBounds(uint32 raw) const;
    EnchantCompoundBounds GetEnchantCompoundBounds(uint32 enchant) const;
    const RecipeCompound* TryRecipeCompound(const Player* player, Reagent reagent) const;
    const GemCompound* TryGemCompound(const Player* player, Reagent reagent) const;
    const EnchantCompound* TryEnchantCompound(const Player* player, const ItemTemplate* item, Reagent reagent) const;
    uint32 CanCompoundRecipe(Reagent reagent, const RecipeCompound* compound, const Player* player) const;
    uint32 CanCompoundEnchant(const ItemTemplate* item, Reagent reagent, const EnchantCompound* compound, const Player* player) const;
    void StackReagents(Reagent& reagent) const;
    void PickGemReagent(const GemCompound* compound, Reagent& reagent) const;
    bool IsNearSpellFocus(const Player* player, uint32 spellFocus) const;
    bool IsRawStone(const ItemTemplate* item) const;
    bool IsSocketStone(const ItemTemplate* item) const;
    const SocketCompound* TrySocketCompound(const Player* player, const ItemTemplate* item, Reagent reagent) const;
    void PickSocketReagent(const SocketCompound* compound, Reagent& reagent) const;
    SocketCompoundBounds GetSocketCompoundBounds(uint32 stone) const;
    uint32 CanCompoundSocket(const ItemTemplate* item, Reagent reagent, const SocketCompound* compound) const;
    uint32 CalculateRecycleAmount(Reagent& reagent) const;
private:
    RecipeCompoundMap m_RecipeCompoundMap;
    GemCompoundMap m_GemCompoundMap;
    EnchantCompoundMap m_EnchantCompoundMap;
    SocketCompoundMap m_SocketCompoundMap;
};

#define xCompoundingMgr CompoundMgr::instance()
#endif // !_H_COMPOUNDING_


