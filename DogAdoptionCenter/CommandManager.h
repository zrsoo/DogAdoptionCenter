#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#endif // COMMANDMANAGER_H

#include <stack>
#include "RepositorySTL.h"
#include "Dog.h"
#include <memory>

class ICommand {
  public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
};

// Add Dog Command...
class AddDogCommand : public ICommand {
  STLRepository<Dog>* repo;
  Dog d;

public:
    AddDogCommand(STLRepository<Dog>* _repo, Dog _d) : repo{_repo}, d{_d} {}
    void execute()    { repo->add(d); }
    void undo()       { repo->removeById(d.get_id());}
    void redo()       { repo->add(d); }
};

// Remove Dog Command...
class RemoveDogCommand : public ICommand {
    STLRepository<Dog>* repo;
    int dogId;
    Dog removedDog;

public:
    RemoveDogCommand(STLRepository<Dog>* _repo, int _dogId) : repo{_repo}, dogId{_dogId} {}
    void execute()    { removedDog = repo->getElementId(dogId); repo->removeById(dogId); }
    void undo()       { repo->add(removedDog); }
    void redo()       { repo->removeById(dogId); }
};

// Update Dog Command...
class UpdateDogCommand : public ICommand
{
    STLRepository<Dog>* repo;
    int dogId;
    Dog dUpdate;
    Dog updatedDog;

public:
    UpdateDogCommand(STLRepository<Dog>* _repo, int _dogId, std::string name, std::string breed, int age, std::string link_photo) :
        repo{_repo}, dogId{_dogId}, dUpdate(name, breed, age, link_photo) {}
    void execute()  { updatedDog = repo->getElementId(dogId); repo->updateElem(dogId, dUpdate); }
    void undo()  { repo->updateElem(dogId, updatedDog); }
    void redo() { repo->updateElem(dogId, dUpdate); }
};


// Command manager...
typedef std::stack<std::shared_ptr<ICommand>> commandStack_t;

class CommandManager {
  commandStack_t mUndoStack;
  commandStack_t mRedoStack;

public:
  CommandManager() {}

  void executeCmd(std::shared_ptr<ICommand> command) {
    mRedoStack = commandStack_t(); // clear the redo stack
    command->execute();
    mUndoStack.push(command);
  }

  void undo() {
    if (mUndoStack.size() <= 0) {
        return;
    }
    mUndoStack.top()->undo();          // undo most recently executed command
    mRedoStack.push(mUndoStack.top()); // add undone command to undo stack
    mUndoStack.pop();                  // remove top entry from undo stack
  }

  void redo() {
    if (mRedoStack.size() <= 0) {
        return;
    }
    mRedoStack.top()->redo();          // redo most recently executed command
    mUndoStack.push(mRedoStack.top()); // add undone command to redo stack
    mRedoStack.pop();                  // remove top entry from redo stack
  }
};
